#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;
///////////////// Webcam/////////////////////
void main()
{
	//string path = "Resources/video.mp4";//����·��
	VideoCapture cap(1);//����ͷ����id ��Ĭ������ͷidΪ 0
	Mat img;

	while (true) {

		cap.read(img);
		imshow("img", img);//��ʾ��Ƶ
		//cvShowImage("imge",&img);
		waitKey(1);//�ȴ�������ÿһ֡ͣ�ٵ�ʱ��

		//����Ƶ��ʾ��ɺ�����û��ͼ���ȡ�������һ������
	}
}