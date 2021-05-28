#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>


float w = 500;
float h = 320;
using namespace std;
using namespace cv;

////////////////////////����ͼ��,���ظ���ͼ//////////////////////
int main()
{
	string path = "Resources/7.jpg";
	Mat img,imgWarp,matrix;
	img = imread(path);
	/*
	316,130,����
	638,312����
	193,388����
	518,529����
	
	
	*/

	Point2f scr[4] =
	{
		{316,130},
		{638,312},
		{193,340},
		{518,529}
	};//ת��ǰ���ĵ㣬�����Ľ�˳��
	for (int i = 0; i < 4; i++)
	{
		circle(img,scr[i],10, Scalar(0, 255, 0),FILLED);
	}
	Point2f dst[4] =
	{
		{0.0,0.0},
		{w,0},
		{0.0,h},
		{w,h}

	};//ת������ĵ�
	matrix = getPerspectiveTransform(scr, dst);//����ת��ģʽ

	warpPerspective(img, imgWarp, matrix, Point(w, h));
	//����ת�����ͼ�񣬸ú�����ɽ� ��ͨ�ӽǸ�Ϊ����ͼ
	imshow("imgWarp", imgWarp);
	imshow("img", img);
	//imshow("matrix", matrix);
	waitKey(100000);
	return 0;
}