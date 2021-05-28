#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>



using namespace std;
using namespace cv;

////////////////////////��״���//////////////////////

void getContours(Mat imgSrc,Mat imgDst)
{
	
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	findContours(imgSrc, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	int area=0;
	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>>conPoly(contours.size());
		//�洢��״�Ľǵ㣬���Ȳ�����������
		vector<Rect>boundRect(contours.size());

		string objType;
		if (area > 1000) {

			double peri = arcLength(contours[i], true);//��ճ���
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(imgDst, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;

			boundRect[i] = boundingRect(conPoly[i]);//��� ������ĸ��������
			rectangle(imgDst, boundRect[i], Scalar(0, 255, 0), 3);//���Ƹ�������
			int objCor = (int)conPoly[i].size();
			float aspRatio = 0.0;
			switch (objCor)
			{
			case 0:
				objType = "error";
				break;
			case 1:
				objType = "error";
				break;
			case 2:
				objType = "error";
				break;
			case 3:
				objType = "Tri";
				break;
			case 4:
				objType = "Rect";
				 aspRatio = (float)boundRect[i].width /(float) boundRect[i].height;
				if(aspRatio>0.95&&aspRatio<1.05)
					objType = "Square";
				break;
			case 5:
				objType = "Pentag";
				break;
			case 6:
				objType = "Circle";
				break;
			default:
				objType = "Circle";
				break;
			}

			putText(imgDst, objType, {boundRect[i].x, boundRect[i].y-5},
				FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 128), 1);
		}
	}
}

int main()
{
	string path = "Resources/shape.png";
	Mat img,imgGray, imgBlur, imgCanny, imgDil, imgEro,imgShape;
	//      �Ҷ�ͼ��,ģ����    ������   ͼ����ǿͼ����ʴ
	img = imread(path);
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil, kernel);

	//��״����Ԥ���� ת��Ϊ�Ҷ�ͼ��ģ������������⣬ͼ����ǿ

	getContours(imgDil,img);


	imshow("img", img);

	//imshow("imgGray", imgGray);
	//imshow("imgBlur", imgBlur);
	//imshow("imgCanny", imgCanny);
	//imshow("imgDil", imgDil);
	//imshow("imgShape", imgShape);

	waitKey(100000);
	






	return 0;
}