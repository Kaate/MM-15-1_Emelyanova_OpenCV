#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <math.h>

using namespace cv;

double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);
}


cv::Mat debugSquares(std::vector<std::vector<cv::Point> > squares, cv::Mat &image)
{
	for (int i = 0; i < squares.size(); i++) {
		//// draw contour
		//cv::drawContours(image, squares, i, cv::Scalar(255, 0, 0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());

		//// draw bounding rect
		//cv::Rect rect = boundingRect(cv::Mat(squares[i]));
		//cv::rectangle(image, rect.tl(), rect.br(), cv::Scalar(0, 255, 0), 2, 8, 0);

		// draw rotated rect
		cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[i]));
		cv::Point2f rect_points[4];
		minRect.points(rect_points);
		for (int j = 0; j < 4; j++) {
			cv::line(image, rect_points[j], rect_points[(j + 1) % 4], cv::Scalar(0, 0, 255), 3, 8); // blue
		}
	}

	return image;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int main( int argc, char** argv ) {

	Mat tmp;
	Mat origin;


	if(argc == 1) {
		std::cout << "Put path to image!" << std::endl;
		return -1;
	} else if (argc == 2) {
	std::cout << argv[1] << std::endl;
	std::string path_to_pict = argv[1];


	origin = imread(path_to_pict);
	tmp = imread(path_to_pict);
	//threshold(picture, gray_picture, 130, 255, THRESH_BINARY);
	}
	if( !origin.data ) { printf("Error loading picture \n"); return -1; }

	std::vector<std::vector<cv::Point> > squares_on_img = { { {97, 672},{904, 643},{931, 1142},{122, 1185} } };

	int delta = 300;
	for (int i = 0; i < 4; ++i) {
		int sigma = getRandomNumber(-delta, delta);
		squares_on_img[0][i].x += sigma;
		sigma = getRandomNumber(0, delta);
		squares_on_img[0][i].y += sigma;
	}
	origin = debugSquares(squares_on_img, origin);

	imwrite("ca_new.png", origin);
 
	return 0;
}