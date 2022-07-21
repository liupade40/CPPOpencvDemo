#include "QuickDemo.h"
#include <iostream>
using namespace std;
//参考 https://blog.csdn.net/m0_46152793/article/details/117380196
//1、显示第一张图片
//色彩空间转换函数 cvtColor
void QuickDemo::colorSpace_Demo(cv::Mat& image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("原图", image);
	imshow("HSV", hsv);
	imshow("灰度", gray);
	imwrite("D:/hsv.jpg", hsv);
	imwrite("D:/gray.jpg", gray);
}
//2、图像对象的创建与赋值
void QuickDemo::mat_creation_demo(Mat& image) {
	//400*400像素大小，每个像素8为无符号整形，3通道的图片。
	Mat m3 = Mat::ones(Size(400, 400), CV_8UC3);
	m3 = Scalar(255, 0, 0);//给三个通道复制BGR，B=255，G=0，R=0
	Mat m4 = m3.clone();
	m4 = Scalar(0, 255, 255);
	//cout << m3 << endl;
	imshow("图像3", m3);
	imshow("图像4", m4);
}
//3、图像像素的读写操作
void QuickDemo::pixel_visit_demo(Mat& image)
{
	Mat b = image.clone();
	int dims = image.channels();
	int h = image.rows;
	int w = image.cols;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			if (dims == 1)
			{
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3)
			{
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}
	imshow("原图", b);
	imshow("像素读写演示", image);
}
//第五节课
//图像像素的操作
void QuickDemo::operators_demo(Mat& image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	dst = image - Scalar(50, 50, 50);
	multiply(image, m, dst);
	imshow("原图", image);
	imshow("dst", dst);
}
Mat src, dst, m;
int lightness = 50;
void on_track(int ,void*) {
	m = Scalar(lightness, lightness, lightness);
	subtract(src, m, dst);
	imshow("亮度调整", dst);
}
//第六节课
//滚动条演示操作 - 调整图片亮度
void QuickDemo::tracking_bar_demo(Mat& image)
{ 
	namedWindow("亮度调整"); 
	dst = Mat::zeros(image.size(), image.type());
	m = Mat::zeros(image.size(), image.type());
	src = image;
	int max_value = 100;
	createTrackbar("value bar:", "亮度调整", &lightness, max_value, on_track);
	on_track(50, 0);
}
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	addWeighted(image, 1, m, 0, b, dst);
	imshow("亮度&对比度调整", dst);
}
//第七节课
//滚动条演示操作 - 传递参数
void QuickDemo::tracking_bar_demo1(Mat& image)
{
	namedWindow("亮度&对比度调整");
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("value bar", "亮度&对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
}
//第八节课
//键盘响应操作
//第九节课
//opencv自带颜色操作
//第十节课
//图像像素的逻辑操作
//第十一节课
//通道的分离与合并
//第十二节课
//图像色彩空间转换
void QuickDemo::inrange_demo(Mat& image)
{
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(35, 34, 46), Scalar(77, 255, 255), mask);
	imshow("mask1", hsv);
	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);
	bitwise_not(mask, mask);
	imshow("mask", mask);
	image.copyTo(redback, mask);
	imshow("roi", redback);
}
//第二十六节课
//直方图的均衡化
void QuickDemo::histogram_eq_demo(Mat& image) {
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("灰度图片", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("直方图", dst);
}