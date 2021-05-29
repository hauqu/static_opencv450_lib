/*

�����䷽�Otsu��������

*/
#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;

Mat img, imgGray, img1;

void showHistogram(Mat img, string window);
void threshold_segmentation_otsu(Mat scr, Mat& dst,vector<int>MT);
//�����ˣ�����opencv�Դ��ķָ���в���
void threshold_segmentation1(Mat scr, Mat& dst, short T);

//�̶���ֵ
int main()
{
	string path = "Resources/jimu_singlecolor.jpg";
	img = imread(path);
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgGray, Size(1, 1), 0.5);
	
	showHistogram(imgGray, "h");
	//vector<int>tt = { 50 ,100};

	//threshold_segmentation_otsu(imgGray, img1, tt);
	threshold(imgGray, img1, 0, 255, THRESH_OTSU);

	imwrite("ʵ��4/img.jpg", img);
	imwrite("ʵ��4/imgGray.jpg", imgGray);
	imwrite("ʵ��4/img_otus.jpg", img1);
	imshow("gray", imgGray);
	imshow("img1", img1);
	waitKey(0);
	
	return 0;
}

void threshold_segmentation_otsu(Mat scr, Mat& dst, vector<int>MT)
{

	//һ����ֵ
	int N = scr.rows * scr.cols;
	const int L = 256;
	int M = MT.size();
	
	vector<double>OWS(0.0,MT[0]);
	scr.copyTo(dst);
	int time = MT[0];

	while (time != 255)
	{

		vector<int>Ni(0, L);//0-255 �ҶȽ�

		vector<double>Wk(0.0, L);
		vector<int>t_Wk(0, L);

		vector<double>Uk(0.0, L);
		vector<int>t_Uk(0, L);


		vector<double>Wj(0.0, M);
		vector<double>Uj(0.0, M);

		int WT = 1;
		double UT = 0.0;
		vector<double>Oj2(0.0, M);

		//��䷽��
		double OW2 = 0.0;
		double OB2 = 0.0;

		//����Ni
		for (int i = 0; i < scr.rows; i++)
		{
			for (int j = 0; j < scr.cols; j++)
			{
				short temp = (short)scr.at<uchar>(i, j);
				Ni[temp]++;
			}
		}

		//����w��k��
		t_Wk[0] = Ni[0];
		Wk[0] = (double)t_Wk[0] / N;
		for (int i = 1; i < L; i++)
		{
			t_Wk[i] = t_Wk[i - 1] + Ni[i];
			Wk[i] = (double)t_Wk[i] / N;
		}

		//����u��k��
		t_Uk[0] = 0;
		Uk[0] = 0.0;
		for (int i = 1; i < L; i++)
		{
			t_Uk[i] = i * Ni[i] + t_Uk[i - 1];
			Uk[i] = t_Uk[i] / N;
		}


		/*
		w(-1) =0
		U(-1) =0;

		*/
		//����Wj
		Wj[0] = Wk[MT[0]];
		for (int j = 1; j < M; j++)
		{
			Wj[j] = Wk[MT[j]] - Wk[MT[j - 1]];
		}

		//����Uj

		Uj[0] = Uk[MT[0]] / Wj[0];
		for (int j = 1; j < M; j++)
		{
			Uj[j] = (Uk[MT[j]] - Uk[MT[j - 1]]) / Wj[j];
		}

		//���� Oj^2
		for (int j = 0; j < M; j++)
		{

			for (int i = MT[j - 1] + 1; i < MT[j]; i++)
			{
				Oj2[j] += (i - Uj[j]) * (i - Uj[j]) * ((double)Ni[i] / N) / Wj[j];
			}
		}

		//����UT

		for (int j = 0; j < M; j++)
		{
			UT += Wj[j] * Uj[j];
		}
		//���� ow^2
		for (int j = 0; j < M; j++)
		{
			OW2 += Wj[j] * Oj2[j];
		}
		OWS.push_back(OW2);
		MT[0]++;
		time++;
	}
	//
	double min = OWS[MT[0]];
	for (int i = MT[0]+1; i < OWS.size(); i++)
	{
		if (OWS[i] < min)
			min = i;
	}
	cout << "OWS min:" << MT[0]<<endl;
	threshold_segmentation1(scr, dst, MT[0]);

}

void showHistogram(Mat img, string window)
{
	// 0-255
	vector<int>rk(256, 0);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			uchar fxy = img.at<uchar>(i, j);
			rk[fxy]++;
		}
	}

	for (auto i = rk.begin(); i != rk.end(); i++)
	{
		(*i) = (*i) / 10;
	}//���ݹ��󣬳���10 ����

	Mat imgH(800, 256 * 4, CV_8UC3, Scalar(64, 64, 64));//����һ��ͼ��
	putText(imgH, window, Point(400, 100), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 0, 128), 2);
	for (int i = 0; i < rk.size(); i++)
	{
		//����ֱ�߼Ӷ���Բ����ֱ��ͼЧ��
		line(imgH, Point(i * 4, 800), Point(i * 4, 800 - rk[i]), Scalar(255, 0, 0));
		circle(imgH, Point(i * 4, 800 - rk[i]), 3, Scalar(255, 255, 0), FILLED);
		if (i % 10 == 0)
		{
			line(imgH, Point(i * 4, 0), Point(i * 4, 800 - rk[i]), Scalar(0, 125, 0));
		}
		if (i%50==0)
		{
			line(imgH, Point(i * 4, 0), Point(i * 4, 800 - rk[i]), Scalar(125, 0, 0));
			putText(imgH, to_string(i), Point(i * 4-25, 20), FONT_HERSHEY_DUPLEX,1,Scalar(0, 255, 0));
		}
		
	}
	imshow(window, imgH);
	//��ʾͼ��
}
void threshold_segmentation1(Mat scr, Mat& dst, short T)
{
	scr.copyTo(dst);
	for (int i = 0; i < scr.rows; i++)
	{
		for (int j = 0; j < scr.cols; j++)
		{
			short temp = (short)scr.at<uchar>(i, j);
			if (temp <= T)
			{
				dst.at<uchar>(i, j) = 0;
			}
			else
			{
				dst.at<uchar>(i, j) = 255;
			}
		}
	}
}
