// LandModel.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "buildingsSimplify.h"
#include "TriMesh.h"




int main()
{
	string heightPath("F:\\ligenProject\\xx3Dmap\\heights\\index.txt");
	vector<GridHeight> heightR;
	vector<IplImage*>cannyImage;
	vector<int> rowNum,colNum;
	vector<double> stdLen;
	vector<double> xmin;
	vector<double> ymax;
	Horizon(heightPath,heightR,cannyImage,rowNum,colNum,stdLen,xmin,ymax);

	//针对每个图形 输入生成图形的范围，以及保存文件的路径
	for(int i=0;i<heightR.size();i++)
	{
		int rowCenter,colCenter,halfRow,halfCol;
		printf("本张图的范围是 行%d 列%d\n xmin：%f  ymax:%f \n 请输入中心点的行，列，半行长，半列长\n",rowNum[i],colNum[i],xmin[i],ymax[i]);
		scanf("%d %d %d %d",&rowCenter,&colCenter,&halfRow,&halfCol);

		int area[4]={rowCenter,colCenter,halfRow,halfCol};

		char tmpPath[120];
		printf("请输入文件路径\n");
		scanf("%s",tmpPath);
		string objPath(tmpPath);
		modelToObj(objPath,cannyImage[i],heightR[i],rowNum[i],colNum[i],xmin[i],ymax[i],stdLen[i],area);
		
	}


	cout<<"All is OK"<<endl;
	getchar();
	

	return 0;
} 