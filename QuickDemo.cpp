#include "QuickDemo.h"
#include <iostream>
using namespace std;
//�ο� https://blog.csdn.net/m0_46152793/article/details/117380196
//1����ʾ��һ��ͼƬ
//ɫ�ʿռ�ת������ cvtColor
void QuickDemo::colorSpace_Demo(cv::Mat& image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("ԭͼ", image);
	imshow("HSV", hsv);
	imshow("�Ҷ�", gray);
	imwrite("D:/hsv.jpg", hsv);
	imwrite("D:/gray.jpg", gray);
}
//2��ͼ�����Ĵ����븳ֵ
void QuickDemo::mat_creation_demo(Mat& image) {
	//400*400���ش�С��ÿ������8Ϊ�޷������Σ�3ͨ����ͼƬ��
	Mat m3 = Mat::ones(Size(400, 400), CV_8UC3);
	m3 = Scalar(255, 0, 0);//������ͨ������BGR��B=255��G=0��R=0
	Mat m4 = m3.clone();
	m4 = Scalar(0, 255, 255);
	//cout << m3 << endl;
	imshow("ͼ��3", m3);
	imshow("ͼ��4", m4);
}
//3��ͼ�����صĶ�д����
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
	imshow("ԭͼ", b);
	imshow("���ض�д��ʾ", image);
}
//����ڿ�
//ͼ�����صĲ���
void QuickDemo::operators_demo(Mat& image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	dst = image - Scalar(50, 50, 50);
	multiply(image, m, dst);
	imshow("ԭͼ", image);
	imshow("dst", dst);
}
Mat src, dst, m;
int lightness = 50;
void on_track(int ,void*) {
	m = Scalar(lightness, lightness, lightness);
	subtract(src, m, dst);
	imshow("���ȵ���", dst);
}
//�����ڿ�
//��������ʾ���� - ����ͼƬ����
void QuickDemo::tracking_bar_demo(Mat& image)
{ 
	namedWindow("���ȵ���"); 
	dst = Mat::zeros(image.size(), image.type());
	m = Mat::zeros(image.size(), image.type());
	src = image;
	int max_value = 100;
	createTrackbar("value bar:", "���ȵ���", &lightness, max_value, on_track);
	on_track(50, 0);
}
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	addWeighted(image, 1, m, 0, b, dst);
	imshow("����&�Աȶȵ���", dst);
}
//���߽ڿ�
//��������ʾ���� - ���ݲ���
void QuickDemo::tracking_bar_demo1(Mat& image)
{
	namedWindow("����&�Աȶȵ���");
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("value bar", "����&�Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));
}
//�ڰ˽ڿ�
//������Ӧ����
//�ھŽڿ�
//opencv�Դ���ɫ����
//��ʮ�ڿ�
//ͼ�����ص��߼�����
//��ʮһ�ڿ�
//ͨ���ķ�����ϲ�
//��ʮ���ڿ�
//ͼ��ɫ�ʿռ�ת��
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
//�ڶ�ʮ���ڿ�
//ֱ��ͼ�ľ��⻯
void QuickDemo::histogram_eq_demo(Mat& image) {
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼƬ", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ", dst);
}