#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;
////////////////������С������/////////////////////////////
int main()
{
	string path = "Resources/man.jpg";
	Mat img = imread(path);
	Mat imgResize ,imgCro;//���ţ�����
	cout << img.size()<<endl;
	
	//resize(img, imgResize,Size(240,320));//���ŵ�����
	resize(img, imgResize, Size(), 0.5, 0.5);//�������ű���
	Rect r(100, 50, 250, 300);//���ϵ�� ����
	
	imgCro = img(r);//�� r ���ּ���

	imshow("man", img);
	imshow("reisze", imgResize);
	imshow("cro", imgCro);

	waitKey(100000);
	return 0;
}
