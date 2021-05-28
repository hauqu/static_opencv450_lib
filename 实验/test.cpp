#include<iostream>

#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{

	Mat img = imread("Resources/img.jpg");

	imshow("imgWindow", img);

	waitKey(0);
	return 0;
}