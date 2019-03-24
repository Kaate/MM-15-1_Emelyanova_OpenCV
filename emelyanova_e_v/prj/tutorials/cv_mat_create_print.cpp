//http://docs.opencv.org/doc/tutorials/core/mat_the_basic_image_container/mat_the_basic_image_container.html#matthebasicimagecontainer

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
  Mat m2x2(Mat::eye(2, 2, CV_8UC1));
  cout << "m1 = " << endl << " " << m2x2 << endl << endl;  

  Mat m3x4(Mat::ones(3, 4, CV_8UC2));
  cout << "m1 = " << endl << " " << m3x4 << endl << endl;  

  Mat m3x2(3, 2, CV_8UC3, Scalar(0, 0, 255));
  cout << "m2x2 = " << endl << " " << m3x2 << endl << endl;  
  
  return 0;
}