#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <math.h>

using namespace cv;

const int alpha_slider_max = 1000;
int alpha_slider = 0;
double alpha = 2.2;
double beta = 50;


Mat src1;
Mat src2;
Mat im_gray;
Mat dst;

int hbins = 256;
int histSize[] = { hbins };
float hranges[] = { 0, 255 };
const float* ranges[] = { hranges };
Mat hist;
int hist_w = 500; int hist_h = 255;
int bin_w = cvRound((double)hist_w / hbins);
Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

void on_trackbar( int, void* ) {
  alpha = (double) alpha_slider/alpha_slider_max ;

  for( int y = 0; y < src1.rows; ++y ) {
    for( int x = 0; x < src1.cols; ++x ) {
		  dst.at<uchar>(y, x) = std::pow((src1.at<uchar>(y, x)), 2) * (alpha_slider + 1);
    }}
  imshow("Destination", dst);

  histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

  calcHist(&dst, 1, 0, Mat(), hist, 1, histSize, ranges, true, true);
  normalize(hist, hist, 0, 255, NORM_MINMAX);

  for (int i = 1; i < hbins; i++)
  {
	  line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
		  Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
		  Scalar(255, 255, 255), 2, 8, 0);
  }
  imshow("Graph", histImage);
}

int main( int argc, char** argv ) {

  if(argc == 1) {
    std::cout << "Put path to image!" << std::endl;
    return -1;
  } else if (argc == 2) {
    std::cout << argv[1] << std::endl;
    std::string path_1 = argv[1];
	src1 = imread(path_1, 0);
	threshold(src1, src1, 128, 255, THRESH_BINARY);
  }
  if( !src1.data ) { printf("Error loading src1 \n"); return -1; }
  dst = Mat::zeros(src1.size(), src1.type());
 
  alpha_slider = 0;

  namedWindow("Destination", WINDOW_AUTOSIZE);
  namedWindow("Graph", WINDOW_AUTOSIZE);

  //Trackbar
  char TrackbarName[50];
  sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
  createTrackbar(TrackbarName, "Destination", &alpha_slider, alpha_slider_max, on_trackbar);
  on_trackbar(alpha_slider, 0);

  waitKey(0);
  return 0;
}