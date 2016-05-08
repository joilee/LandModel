//#include "array2D.h"
#include "readGrid.h"
#include <cv.h>
#include <highgui.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

/************************************************************************/
/*  thetaToGrey     (��theta ��0~Pi/2��ӳ�䵽�Ҷ�ֵ(0~255)) 

*/
/************************************************************************/

 void thetaToGrey(vector<vector<double> > &src,vector<vector<int> >&grey,int row,int col)
{
	
	//grey.resize(row,vector<int>(col));
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
		{
			double tmpScale=255*src[i][j]/M_PI_2;
			int greyValue=floor(tmpScale);
			if(greyValue<0)greyValue=0;
			if(greyValue>255)greyValue=255;
			grey[i][j]=greyValue;
		}
   //return grey;
}


/************************************************************************/
/* ����ά�����ת��ͼƬ

*/
/************************************************************************/
IplImage * arrayToImage(vector<vector<double> >& src,int row,int col)
{
	CvSize sizeImage=CvSize(col,row);
	IplImage *srcImage = cvCreateImage(sizeImage, IPL_DEPTH_8U, 1);
	vector<vector<int> > greyMatrix;
	greyMatrix.resize(row,vector<int>(col));
	thetaToGrey(src,greyMatrix,row,col);//�ǵ�Ҫ�ͷ��ڴ�
	
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
		{
			cvSetReal2D(srcImage,i,j,255-greyMatrix[i][j]);
		}
		
		cvShowImage("nornal ����", srcImage);
		
     //delete_Array2D(greyMatrix, row, col);//�ͷ��ڴ�

	 return srcImage;
}


/************************************************************************/
/* ��canny�㷨�����ɵ�ͼƬ�ı�Ե��Ϣ��ȡ������
*/
/************************************************************************/

void imageToArray(vector<vector<int> >&cannyPoints,IplImage *src,int row ,int col,int& nVertex)
{
	uchar *ptr;

	for (int i=0; i<row; i++)
	{
		ptr = (uchar*)src->imageData + i*src->widthStep;
		for (int j=0; j<col; j++)
		{
			cannyPoints[i][j] = (int)*(ptr+j);
			if(cannyPoints[i][j]!=0)
			{
				nVertex++;
			}
		}
	}

}