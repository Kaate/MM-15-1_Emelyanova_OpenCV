#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include<fstream>
#include<iostream>
#include <math.h>

using namespace cv;

double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);
}

void find_squares_test(Mat image, std::vector<std::vector<Point> >& squares) {
	Mat blur(image), canny;
	GaussianBlur(image, blur, Size(3, 3), 0, 0, BORDER_DEFAULT);

	Canny(blur,            // input image
		canny,                    // output image
		30,                        // low threshold
		200);

	dilate(canny, canny, Mat(), Point(-1, -1));
	//imshow("test", canny);
	std::vector<std::vector<Point> > contours;
	findContours(canny, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	std::vector<Point> approx;
	for (size_t i = 0; i < contours.size(); i++)
	{

		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

		if (approx.size() == 4 &&
			fabs(contourArea(Mat(approx))) > 1000 &&
			isContourConvex(Mat(approx)))
		{
			double maxCosine = 0;

			for (int j = 2; j < 5; j++)
			{
				double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
				maxCosine = MAX(maxCosine, cosine);
			}

			if (maxCosine < 0.3)
				squares.push_back(approx);
		}
	}
}

void find_squares(Mat image, std::vector<std::vector<Point> >& squares)
{
	Mat blurred(image);
	medianBlur(image, blurred, 9);

	Mat gray0(blurred.size(), CV_8U), gray;
	std::vector<std::vector<Point> > contours;

	// find squares in every color plane of the image
	for (int c = 0; c < 3; c++)
	{
		int ch[] = { c, 0 };
		mixChannels(&blurred, 1, &gray0, 1, ch, 1);
		const int threshold_level = 1;
		for (int l = 0; l < threshold_level; l++)
		{

			if (l == 0)
			{
				Canny(gray0, gray, 20, 50, 3); // 10 30

				dilate(gray, gray, Mat(), Point(-1, -1));
			}
			else
			{
				gray = gray0 >= (l + 1) * 255 / threshold_level;
				
			}
			//imshow("test", gray);
			findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
			
			std::vector<Point> approx;
			for (size_t i = 0; i < contours.size(); i++)
			{

				approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

				if (approx.size() == 4 &&
					fabs(contourArea(Mat(approx))) > 1000 &&
					isContourConvex(Mat(approx)))
				{
					double maxCosine = 0;

					for (int j = 2; j < 5; j++)
					{
						double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
						maxCosine = MAX(maxCosine, cosine);
					}

					if (maxCosine < 0.3)
						squares.push_back(approx);
				}
			}
		}
	}
}

double calc_accuracy(std::vector<Point> markup, std::vector<std::vector<cv::Point> > squares) {

	float max_dig = 0.0;
	int index_max;
	for (int j = 0; j < squares.size(); ++j) {
		cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[j]));
		cv::Point2f rect_points[4];
		minRect.points(rect_points);
		float diagonal = sqrt((rect_points[0].x - rect_points[2].x)* (rect_points[0].x - rect_points[2].x) + (rect_points[0].y - rect_points[2].y)*(rect_points[0].y - rect_points[2].y));
		if (diagonal > max_dig) {
			max_dig = diagonal; index_max = j;
		}
	}

	double sum = 0.0;
	for (int i = 0; i < 4; ++i) {
		sum = std::pow((markup[i].x - squares[index_max][i].x), 2) + std::pow((markup[i].y - squares[index_max][i].y), 2);
	}

	double accuracy = std::sqrt(std::abs(sum));
	return accuracy;
}

cv::Mat debugSquares(std::vector<std::vector<cv::Point> > squares, cv::Mat &image)
{
	float max_dig = 0.0;
	int index_max;
	for (int j = 0; j < squares.size(); ++j) {
		cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[j]));
		cv::Point2f rect_points[4];
		minRect.points(rect_points);
		float diagonal = sqrt((rect_points[0].x - rect_points[2].x)* (rect_points[0].x - rect_points[2].x) + (rect_points[0].y - rect_points[2].y)*(rect_points[0].y - rect_points[2].y));
		if (diagonal > max_dig) {
			max_dig = diagonal; index_max = j;
		}
	}
	cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[index_max]));
	cv::Point2f rect_points[4];
	minRect.points(rect_points);

	for (int j = 0; j < 4; j++) {
		cv::line(image, rect_points[j], rect_points[(j + 1) % 4], cv::Scalar(0, 0, 255), 1, 8);
	}

	std::ofstream out;         
	out.open("D:/study/emelyanova_e_v/MM-15-1_Emelyanova_OpenCV/emelyanova_e_v/squad.txt"); 
	if (out.is_open())
	{
		for(int i = 0; i<4; ++i)
			out << squares[index_max][i] << std::endl;
	}

	return image;
}

Mat Gaussian(const Mat &image, std::vector<std::vector<cv::Point> > squares) {

	float max_dig = 0.0;
	int index_max;
	for (int j = 0; j < squares.size(); ++j) {
		cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[j]));
		cv::Point2f rect_points[4];
		minRect.points(rect_points);
		float diagonal = sqrt((rect_points[0].x - rect_points[2].x)* (rect_points[0].x - rect_points[2].x) + (rect_points[0].y - rect_points[2].y)*(rect_points[0].y - rect_points[2].y));
		if (diagonal > max_dig) {
			max_dig = diagonal; index_max = j;
		}
	}

	Mat mask;
	cv::GaussianBlur(image, mask, Size(145, 145), 4);

	cv::Mat mask_img = cv::Mat::zeros(image.rows, image.cols, CV_8U); // all 0
	cv::Mat mask_invert = cv::Mat::zeros(image.rows, image.cols, CV_8U); // all 0

	fillConvexPoly(mask_img, squares[index_max], Scalar(255));
	//imshow("test", mask_img);
	Mat tmp(image.rows, image.cols, CV_8UC3, Scalar(0));
	Mat tmp1(image.rows, image.cols, CV_8UC3, Scalar(0));

	bitwise_not(mask_img, mask_invert, mask_img);
	bitwise_or(image, image, tmp, mask_invert);
	bitwise_or(mask, mask, tmp1, mask_img);
	bitwise_or(tmp1, tmp, image, mask_img);
	return image;
}

int main( int argc, char** argv ) {
	//namedWindow("test", WINDOW_AUTOSIZE);
	Mat tmp;
	Mat origin;
	std::vector<std::vector<cv::Point> > squares_on_img; 
	std::vector<std::vector<cv::Point> > markup;

	
	if(argc == 1) {
		std::cout << "Put path to image!" << std::endl;
		return -1;
	} else if (argc == 2) {
	std::cout << argv[1] << std::endl;
	std::string path_to_pict = argv[1];
	origin = imread(path_to_pict);
	tmp = imread(path_to_pict);
	//threshold(origin, tmp, 200, 255, THRESH_BINARY);
	}
	/////////////////////// PARSE MART

	if( !origin.data ) { printf("Error loading picture \n"); return -1; }

	find_squares(tmp, squares_on_img);
	find_squares_test(tmp, squares_on_img);
	if (squares_on_img.size() == 0) {
		std::cout << "no quad" << std::endl;
		std::ofstream out;          // поток для записи
		out.open("D:/study/emelyanova_e_v/MM-15-1_Emelyanova_OpenCV/emelyanova_e_v/squad.txt"); // окрываем файл для записи
		out << -1;
		waitKey(0);
		return -1;

	}
	namedWindow("Counter", WINDOW_AUTOSIZE);


	Gaussian(origin, squares_on_img);
	debugSquares(squares_on_img, origin);
	imshow("Counter", origin);

	waitKey(0);
	return 0;
}