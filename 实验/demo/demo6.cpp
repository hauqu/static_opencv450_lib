#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;
////////////////��ͼ������/////////////////////////////
int main()
{
	Mat img(512, 512, CV_8UC3, Scalar(64, 64, 64));//����һ��ͼ��
	circle(img, Point(256, 256), 155, Scalar(58, 69, 25), FILLED);//��һ��Բ
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255),FILLED);
	//��һ������
	line(img, Point(10, 10), Point(300, 300),Scalar(255,255,0));
	//��һ����
	putText(img,"ni gai si",Point(200,200),FONT_HERSHEY_DUPLEX,2,Scalar(0,0,128),2);
	//���ı�
	imshow("img", img);
	
	

	waitKey(100000);
	return 0;
}
