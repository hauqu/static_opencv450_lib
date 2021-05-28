#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<conio.h>


using namespace std;
using namespace cv;
//////////////////base function ///////////////////////////
int main()
{
	string path = "Resources/man.jpg";
	Mat img = imread(path);
	Mat imgGray,imgBlur,imgCanny,imgDil,imgEro;
	//�Ҷ�ͼ��,ģ����������ͼ����ǿ��ͼ����ʴ
	cvtColor(img, imgGray,COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3,3), 3, 0);
	//��˹ģ��
	Canny(imgBlur, imgCanny, 25, 75);
	//
	Mat kernal = getStructuringElement(MORPH_RECT,Size(3, 3));

	dilate(imgCanny, imgDil, kernal);

	erode(imgDil, imgEro, kernal);

	imshow("img", img);
	imshow("imgGray", imgGray);
	imshow("imgBlur", imgBlur);
	imshow("imgCanny", imgCanny);
	imshow("imgDilation", imgDil);
	imshow("imgEro", imgEro);
	waitKey(100000);

	return 0;
}