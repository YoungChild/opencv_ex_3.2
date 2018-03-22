#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
#define WINDOW_NAME "3.2"

const int g_nMaxAlphaValue = 100;
Mat g_srcImage1, g_srcImage2, g_srcImage3, g_srcImage;
int g_nAlphaValueSlider;
double g_dAlphaValue, g_dBetaValue;
char TrackbarName[50];


void on_Trackbar(int, void*){
	//�ص�����
//	g_srcImage3 = g_srcImage1.clone();
	g_srcImage1.copyTo(g_srcImage3);
	//clone,copyTo ����

	g_dAlphaValue = (double)getTrackbarPos(TrackbarName, WINDOW_NAME) / g_nMaxAlphaValue;
	g_dBetaValue = (double)(1.0 - g_dAlphaValue);
	Mat imageROI = g_srcImage3(Rect(800, 350, g_srcImage2.cols, g_srcImage2.rows));
	//����ROI ROI�ı���ԭͼҲ��ı�

	addWeighted(imageROI, 1, g_srcImage2, g_dBetaValue, 0., imageROI);
	//ͼ���ں�

	imshow(WINDOW_NAME, g_srcImage3);

}

int main(int argc, char** argv){
	g_srcImage1 = imread("Dota.jpg");
	g_srcImage2 = imread("Dota_logo.jpg");
	if (!g_srcImage1.data){ 
		printf("��һ����ȡʧ��"); 
		return 1; 
	}
//	cout << g_srcImage1 << endl;
	if (!g_srcImage2.data){
		printf("�ڶ�����ȡʧ��");
		return 1;
	}

	g_nAlphaValueSlider = 30;
	//���ó�ʼֵ
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//��������
	sprintf(TrackbarName, "͸����%d", g_nMaxAlphaValue);
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
	//����������
	on_Trackbar(g_nAlphaValueSlider, 0);
	//ֻ������һ�Σ��������ó�ʼֵ,�Լ���һ��ͼ�����ʾ��ɾ�����һ�ν���Ϊ��
	waitKey(0);

	return 0;

}