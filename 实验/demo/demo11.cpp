#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;
///////////////// cam face /////////////////////
void main()
{
	
	VideoCapture cap(2);
	Mat img;
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	//����ģ��
	if (faceCascade.empty())
	{
		cout << "XML file load fail" << endl;
	}

	

	
	while (true) {

		cap.read(img);
		vector<Rect>faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);
		for (int i = 0; i < faces.size(); i++)
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 3);
		imshow("img", img);//��ʾ��Ƶ
		//cvShowImage("imge",&img);
		waitKey(1000);//�ȴ�������ÿһ֡ͣ�ٵ�ʱ��

		//����Ƶ��ʾ��ɺ�����û��ͼ���ȡ�������һ������
	}
}