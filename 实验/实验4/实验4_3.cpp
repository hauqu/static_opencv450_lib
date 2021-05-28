/*

������Զ����޷�����


*/
#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;

void OptimSegmentation(unsigned char* inputimage, int height, int width);
void showHistogram(Mat img, string window);

Mat img,imgGray;
int main()
{
   img = imread("Resources/jimu_singlecolor.jpg");
    
    cvtColor(img, imgGray, COLOR_RGB2GRAY);
   
    showHistogram(imgGray, "H");
    int height = imgGray.rows;
    int width = imgGray.cols;
    uchar* covertimage = new uchar[height * width];
    uchar* p;
    int i, j;
    for (i = 0; i < height; i++)
    {
        p = imgGray.ptr<uchar>(i);
        for (j = 0; j < width; j++)
        {
            covertimage[i * width + j] = p[j];
        }
    }
    OptimSegmentation(covertimage, width, height);
    Mat outimage(height, width, CV_8UC1, covertimage); //һά����תMat��
    //cvNamedWindow("ͼ����ʾ", CV_WINDOW_AUTOSIZE);
    imshow("output", outimage);
    waitKey(0);
    delete[] covertimage;
    return 0;
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
		if (i % 50 == 0)
		{
			line(imgH, Point(i * 4, 0), Point(i * 4, 800 - rk[i]), Scalar(125, 0, 0));
			putText(imgH, to_string(i), Point(i * 4 - 25, 20), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0));
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
void OptimSegmentation(unsigned char* inputimage, int height, int width)
{
    //1.����ֱ��ͼ
    int* histarray = new int[256];
    int i, x, y;
    for (i = 0; i < 256; i++)
    {
        histarray[i] = 0;
    }
    //�м����
    int temp, temp1, temp2;
    //ͳ�ƻҶ�ֱ��ͼ
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            int k = width * y + x;
            temp = inputimage[k];
            histarray[temp]++;
        }
    }

    //2.����������ֵ
//  int minT = 0,maxT=0;
    double MinGrayValue = 0, MaxGrayValue = 0;
    //float P0 = 0.0, Pt = 0.0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            int k = width * y + x;
            temp1 = inputimage[k];
            if (MinGrayValue > temp1)
                MinGrayValue = temp1;//��С�Ҷ�ֵ
        }
    }
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            int k = width * y + x;
            temp2 = inputimage[k];
            if (MaxGrayValue < temp2)
                MaxGrayValue = temp2;//���Ҷ�ֵ
        }
    }
    double newT = (MinGrayValue + MaxGrayValue) / 2;
    //std::cout << newT << std::endl;
    double T = 0.0;
    double S0 = 0.0, N1 = 0.0; //��ʼ��������ֵ��Ԫ�صĸ�������Ҷ���ֵ
    double S1 = 0.0, N2 = 0.0; //��ʼ��С����ֵ��Ԫ�صĸ�������Ҷ���ֵ
    while (abs(newT - T) > 0)
    {
        T = newT;
        //std::cout << T << std::endl;
        for (i = 0; i < 256; i++)
        {
            if (i > T)
            {
                S0 = S0 + histarray[i]; //��¼������ֵ��Ԫ�ظ�������Ҷ���ֵ
                //N1 = N1 + 1;
                N1 += i * histarray[i];
            }
            else
            {
                S1 = S1 + histarray[i];
                //N2 = N2 + 1;
                N2 += i * histarray[i];
            }
        }
        double T0 = N1 / S0;  //��������ֵ
        double T1 = N2 / S1;
        newT = (T0 + T1) / 2;
        //  std::cout << newT << std::endl;
        S0 = 0.0; N1 = 0.0;  //���ó�ֵ
        S1 = 0.0; N2 = 0.0;
    }

    //3.ͼ���ֵ��
//  unsigned char *outimage1=new unsigned char[height*width];
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            int k = width * y + x;
            //outimage1[k] = inputimage[k];
            //std::cout << outimage1[k] << std::endl;
        //  std::cout << T << std::endl;
            if (inputimage[k] > T)   //����Ϊ��ɫ
                inputimage[k] = 255;

            else
                inputimage[k] = 0;

        }
    }
    delete[] histarray;
    //delete[] outimage1;
}