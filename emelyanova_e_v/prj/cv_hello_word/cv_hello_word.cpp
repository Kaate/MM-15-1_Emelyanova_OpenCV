#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{

   Mat image_result(200, 200, CV_8U, Scalar(255));

   Mat image_source1(100, 100, CV_8U, Scalar(0));
   circle(image_source1, Point(50, 50), 30, Scalar(255), -1);
   image_source1.copyTo(image_result(Rect(0, 100, image_source1.cols, image_source1.rows)));
   
   Mat image_source2(100, 100, CV_8U, Scalar(255));
   circle(image_source2, Point(50, 50), 30, Scalar(0), -1);
   image_source2.copyTo(image_result(Rect(0, 0, image_source2.cols, image_source2.rows)));

   Mat image_source3(100, 100, CV_8U, Scalar(127));
   circle(image_source3, Point(50, 50), 30, Scalar(255), -1);
   image_source3.copyTo(image_result(Rect(100, 0, image_source3.cols, image_source3.rows)));

   Mat image_source4(100, 100, CV_8U, Scalar(127));
   circle(image_source4, Point(50, 50), 30, Scalar(0), -1);
   image_source4.copyTo(image_result(Rect(100, 100, image_source3.cols, image_source3.rows)));
   
   Mat image_result1(400, 400, CV_8U, Scalar(255));
   image_result.copyTo(image_result1(Rect(0, 0, image_result.cols, image_result.rows)));
   //1
   Mat dst(200, 200, CV_8U, Scalar(255));

   float kernel1[4];
   kernel1[0] = 1;
   kernel1[1] = 0;

   kernel1[2] = 0;
   kernel1[3] = -1;

   Mat kernel_mat1 = Mat(2, 2, CV_32FC1, kernel1);
   filter2D(image_result, dst, CV_32FC1, kernel_mat1);
   dst.copyTo(image_result1(Rect(0, 200, dst.cols, dst.rows)));
   //2
   Mat dst1(200, 200, CV_8U, Scalar(255));

   float kernel[4];
   kernel[0] = 0;
   kernel[1] = 1;

   kernel[2] = -1;
   kernel[3] = 0;

   Mat kernel_mat = Mat(2, 2, CV_32FC1, kernel);
   filter2D(image_result, dst1, CV_32FC1, kernel_mat);
   dst1.copyTo(image_result1(Rect(200, 200, dst.cols, dst.rows)));

   imshow("cv::circle", image_result1);

   waitKey(0);
   return 0;
}