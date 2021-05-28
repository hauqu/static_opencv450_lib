#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;
///////////////// find color /////////////////////

vector<vector<int>>myColors
{
	{0,0,0,180,255,46},//��ɫ
	{0,0,46,180,43,220},//��ɫ
	{0,0,221,180,30,255},//��ɫ
	{0,43,46,10,255,255},//��ɫ
	{11,43,46,25,255,255},//��ɫ
	{26,43,46,34,255,255},//��ɫ
	{35,43,46,77,255,255},//��ɫ
	{78,43,46,99,255,255},//��ɫ
	{100,43,46,124,255,255},//��ɫ
	{125,43,46,155,255,255}//��ɫ

};
vector<Scalar>myColorValues
{
	{255,0,255},//for ��ɫ
	{0,255,0}//for ��ɫ
};


void findColor(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);//����HSVͼ��

	for (int i = 0; i < myColors.size(); i++)
	{
		Mat mask;
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		imshow(to_string(i), mask);
	}
	
	
	//�� imgHSV��ȡ��lower �� upper��Χ����ɫ���ֵ� mask
}
void main()
{

	VideoCapture cap(2);
	Mat img;
	


	while (true) {

		cap.read(img);
		findColor(img);
		imshow("img", img);//��ʾ��Ƶ
		//cvShowImage("imge",&img);
		waitKey(1);//�ȴ�������ÿһ֡ͣ�ٵ�ʱ��

		//����Ƶ��ʾ��ɺ�����û��ͼ���ȡ�������һ������
	}
}