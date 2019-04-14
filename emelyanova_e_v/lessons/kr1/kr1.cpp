#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{

	Mat image_result(100, 300, CV_8U, Scalar(255));
	Mat image_result2(200, 200, CV_8U, Scalar(255));
	Mat image(200, 300, CV_8U, Scalar(255));


	rectangle(image, Point(0, 0), Point(300/3, 300/3), Scalar(127), -1);
	circle(image, Point(150/3, 150/3), 30, Scalar(0), -1);

	rectangle(image, Point(300 / 3, 0), Point(600 / 3, 300 / 3), Scalar(0), -1);
	circle(image, Point(450 / 3, 150 / 3), 30, Scalar(255), -1);

	rectangle(image, Point(0, 300 / 3), Point(300 / 3, 600 / 3), Scalar(0), -1);
	circle(image, Point(150 / 3, 450 / 3), 30, Scalar(127), -1);

	rectangle(image, Point(600 / 3, 0), Point(900 / 3, 300 / 3), Scalar(255), -1);
	circle(image, Point(750 / 3, 150 / 3), 30, Scalar(127), -1);

	rectangle(image, Point(300 / 3, 300 / 3), Point(600 / 3, 600 / 3), Scalar(255), -1);
	circle(image, Point(450 / 3, 450 / 3), 30, Scalar(0), -1);

	rectangle(image, Point(600 / 3, 300 / 3), Point(900 / 3, 600 / 3), Scalar(127), -1);
	circle(image, Point(750 / 3, 450 / 3), 30, Scalar(255), -1);

	// FILTER 1

	float kernel1[4];
	kernel1[0] = 1;
	kernel1[1] = 0;

	kernel1[2] = 0;
	kernel1[3] = -1;

	Mat kernel_mat1 = Mat(2, 2, CV_32FC1, kernel1);
	filter2D(image, image_result, -1, kernel_mat1, cv::Point(-1, -1), 128, cv::BORDER_REPLICATE);

	// FILTER 2

	Mat dst1(200, 200, CV_8U, Scalar(255));

	float kernel[4];
	kernel[0] = 0;
	kernel[1] = 1;

	kernel[2] = -1;
	kernel[3] = 0;

	Mat kernel_mat = Mat(2, 2, CV_32FC1, kernel);
	filter2D(image_result, dst1, CV_32FC1, kernel_mat);
	filter2D(image, image_result2, -1, kernel_mat, cv::Point(-1, -1), 128, cv::BORDER_REPLICATE);

	imshow("cv::circle", image);
	imshow("cv::filter1", image_result);
	imshow("cv::filter2", image_result2);

	waitKey(0);
	return 0;
}