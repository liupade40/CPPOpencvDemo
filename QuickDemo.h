#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
class QuickDemo
{
public:
	void colorSpace_Demo(cv::Mat &img);
	void mat_creation_demo(Mat& image);
	void pixel_visit_demo(Mat& image);
	void operators_demo(Mat& image);
	void tracking_bar_demo(Mat& image); 
	void tracking_bar_demo1(Mat& image); 
	void inrange_demo(Mat& image);
	void histogram_eq_demo(Mat& image);
};

