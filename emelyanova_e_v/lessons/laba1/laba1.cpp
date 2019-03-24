#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;

int main()
{
	//SPLIT CHANNELS
	Mat image_res(512, 512, CV_8UC3, Scalar(255, 255, 255));
	Mat image(Mat::zeros(256, 256, CV_8UC1));

	image = imread("D:/study/emelyanova_e_v/sample/testdata/kek.jpg");
	image.copyTo(image_res(Rect(0, 0, image.cols, image.rows)));

	Mat img_temp(Mat::zeros(256, 256, CV_8UC1));
	Mat rgb[3];
	Mat rgb1[3];
	Mat rgb2[3];

	split(image, rgb);
	rgb[0] = rgb[1] = Mat::zeros(Size(image.rows, image.cols), CV_8UC1);
	merge(rgb, 3, img_temp);
	img_temp.copyTo(image_res(Rect(0, 256, image.cols, image.rows)));

	split(image, rgb1);
	rgb1[1] = rgb1[2] = Mat::zeros(Size(image.rows, image.cols), CV_8UC1);
	merge(rgb1, 3, img_temp);
	img_temp.copyTo(image_res(Rect(256, 0, image.cols, image.rows)));

	split(image, rgb2);
	rgb2[0] = rgb2[2] = Mat::zeros(Size(image.rows, image.cols), CV_8UC1);
	merge(rgb2, 3, img_temp);
	img_temp.copyTo(image_res(Rect(256, 256, image.cols, image.rows)));

	imshow("SPLIT CHANNELS", image_res);

	//SHOW HISTOGRAMM
	Mat img_tmp;
	img_tmp = image;

	int hbins = 256;
	int channels[] = { 0 }; 
	int histSize[] = { hbins };
	float hranges[] = { 0, 255 };
	const float* ranges[] = { hranges };

	MatND b_hist, g_hist, r_hist;
	Mat rgb3[3];
	split(img_tmp, rgb3);

	calcHist(&rgb3[0], 1, 0, Mat(), b_hist, 1, histSize, ranges, true, false);
	calcHist(&rgb3[1], 1, 0, Mat(), g_hist, 1, histSize, ranges, true, false);
	calcHist(&rgb3[2], 1, 0, Mat(), r_hist, 1, histSize, ranges, true, false);

	normalize(b_hist, b_hist, 0, 255, NORM_MINMAX);
	normalize(g_hist, g_hist, 0, 255, NORM_MINMAX);
	normalize(r_hist, r_hist, 0, 255, NORM_MINMAX);

	int hist_w = 500; int hist_h = 255;
	int bin_w = cvRound((double)hist_w / hbins);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	for (int i = 1; i < hbins; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("SHOW HISTOGRAM OF ORIGINAL", histImage);



	waitKey(0);
	return 0;
}