// LandModel.cpp : �������̨Ӧ�ó������ڵ㡣
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

	//���ÿ��ͼ�� ��������ͼ�εķ�Χ���Լ������ļ���·��
	for(int i=0;i<heightR.size();i++)
	{
		int rowCenter,colCenter,halfRow,halfCol;
		printf("����ͼ�ķ�Χ�� ��%d ��%d\n xmin��%f  ymax:%f \n ���������ĵ���У��У����г������г�\n",rowNum[i],colNum[i],xmin[i],ymax[i]);
		scanf("%d %d %d %d",&rowCenter,&colCenter,&halfRow,&halfCol);

		int area[4]={rowCenter,colCenter,halfRow,halfCol};

		char tmpPath[120];
		printf("�������ļ�·��\n");
		scanf("%s",tmpPath);
		string objPath(tmpPath);
		modelToObj(objPath,cannyImage[i],heightR[i],rowNum[i],colNum[i],xmin[i],ymax[i],stdLen[i],area);
		
	}


	cout<<"All is OK"<<endl;
	getchar();
	

	return 0;
} 