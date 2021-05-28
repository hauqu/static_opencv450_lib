#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>



using namespace std;
using namespace cv;

////////////////////////��ɫ���--����ͷ�汾//////////////////////

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;
VideoCapture cap(2);//����ͷ����id ��Ĭ������ͷidΪ 0
int main()
{
	
	
	Mat img, imgGray, imgHSV, mask;
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Mmax", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
	while (true) {

		cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);//����HSVͼ��


		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		//�� imgHSV��ȡ��lower �� upper��Χ����ɫ���ֵ� mask
		imshow("img", img);
		//imshow("imgGray", imgGray);
		//imshow("imgHSV", imgHSV);
		imshow("imgMask", mask);
		waitKey(100);

		
	}
	
	return 0;
}