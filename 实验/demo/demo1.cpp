#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;
///////////////// images/////////////////////
void main()
{
	string path = "Resources/img.jpg";//����·��
	Mat img = imread(path);//��ȡͼƬ
	
	imshow("img", img);//��ʾͼƬ
		//cvShowImage("imge",&img);
	waitKey(1000);//�ȴ�
		while (true)
		{

		}
	
}