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
	//回调函数
//	g_srcImage3 = g_srcImage1.clone();
	g_srcImage1.copyTo(g_srcImage3);
	//clone,copyTo 均可

	g_dAlphaValue = (double)getTrackbarPos(TrackbarName, WINDOW_NAME) / g_nMaxAlphaValue;
	g_dBetaValue = (double)(1.0 - g_dAlphaValue);
	Mat imageROI = g_srcImage3(Rect(800, 350, g_srcImage2.cols, g_srcImage2.rows));
	//设置ROI ROI改变其原图也会改变

	addWeighted(imageROI, 1, g_srcImage2, g_dBetaValue, 0., imageROI);
	//图像融合

	imshow(WINDOW_NAME, g_srcImage3);

}

int main(int argc, char** argv){
	g_srcImage1 = imread("Dota.jpg");
	g_srcImage2 = imread("Dota_logo.jpg");
	if (!g_srcImage1.data){ 
		printf("第一幅读取失败"); 
		return 1; 
	}
//	cout << g_srcImage1 << endl;
	if (!g_srcImage2.data){
		printf("第二幅读取失败");
		return 1;
	}

	g_nAlphaValueSlider = 30;
	//设置初始值
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//创建窗口
	sprintf(TrackbarName, "透明度%d", g_nMaxAlphaValue);
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
	//创建滑动条
	on_Trackbar(g_nAlphaValueSlider, 0);
	//只会运行一次，用于设置初始值,以及第一张图像的显示。删除后第一次进入为空
	waitKey(0);

	return 0;

}