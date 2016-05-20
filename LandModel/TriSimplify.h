#include "Mesh.h"
#include <math.h>
#include <map>
#include <vector>
using namespace std;

class SimEdge
{
public:
	VERTEX2D_PTR v1;
	VERTEX2D_PTR v2;
	int id1,id2;
	SimTri * triPtr[2];
	int triNum;

	bool inQueue;
	SimEdge(int _id1,int _id2):id1(_id1),id2(_id2)
	{
		triNum=0;
		inQueue=false;
	}
	
};

class SimTri
{
public:
	int id1;
	int id2;
	int id3;
	SimEdge *e[3];
	bool isDeleted;//记录是否被合并。

	SimTri(int i1,int i2,int i3):id1(i1),id2(i2),id3(i3)
	{
	 isDeleted=false;
	}
protected:
private:
};


/************************************************************************/
/* 简化三角形 将共线的三角形合并                                        */
/************************************************************************/
void simplifyTri(MESH_PTR pMesh)
{
	
	double standardArea=(stepLength^2)/2;
	TRIANGLE_PTR pTri = pMesh->pTriArr;
	int* pi;

	//step0:设置初始变量
	map<pair<int,int>,SimEdge*> edgeCollect;
	vector<SimTri *> originTri;
	vector<SimEdge*> originEdge;
	int oringTriCount=0,originEdgeCount=0;

	while(pTri != NULL)	
	{

		int id[3];
		double x[3],y[3],z[3];
		pi = &(pTri->i1);
		for (int j=0; j<3; j++)	
		{	
			id[j] = *pi++;	
			id[j]=id[j]-2;
			x[j]=((VERTEX2D_PTR)(pMesh->pVerArr+id[j]))->x;
			y[j]=((VERTEX2D_PTR)(pMesh->pVerArr+id[j]))->y;
			z[j]=((VERTEX2D_PTR)(pMesh->pVerArr+id[j]))->z;
		}

		//step1:对水平且面积不等于正方形网格一半的三角形，检测并处理 true转step2 false转step4
		//判断是否水平
		double x1=x[1]-x[0];
		double x2=x[2]-x[0];
		double y1=y[1]-y[0];
		double y2=y[2]-y[0];
		double tmpArea=fabs( x1*y2 - y1*x2);
		if(z[0]==z[1]&&z[0]==z[2]&&(tmpArea<standardArea))
		{
		//step2:遍历三个边，每个边都要加入边表
			SimTri *tmpTri=new SimTri(id[0],id[1],id[2]);
			originTri.push_back(tmpTri);
			oringTriCount++;
			 for(int k=0;k<3;k++)
			 {
				 int smallId,bigId;
				 if(id[k]>id[(k+1)%3])//01 12 20
				 {
					 smallId=id[(k+1)%3];bigId=id[k];
				 }else
				 {
					 smallId=id[k];bigId=id[(k+1)%3];
				 }

				 map<pair<int,int>,SimEdge*>::iterator it=edgeCollect.find(pair<int,int>(smallId,bigId));
				 if(it!=edgeCollect.end())
				 {
					//step 2.1 该边已经存在
				 }else
				 {
					 //step 2.2 该边不存在，需要加入该边
					 pair<int,int> p1=make_pair(smallId,bigId);
					 SimEdge *tmpEdge=new SimEdge(smallId,bigId);

					 //在三角形和边中 互相设置指针
					 if(tmpEdge->triPtr[0]==NULL)
					 {
						tmpEdge->triPtr[0]=tmpTri;
						tmpEdge->triNum=1;
					 }else
					 {
						 tmpEdge->triPtr[1]=tmpTri;
						 tmpEdge->triNum=2;
					 }
					 tmpTri->e[k]=tmpEdge;
					 edgeCollect.insert(make_pair(p1,tmpEdge));
					 originEdge.push_back(tmpEdge);
					 originEdgeCount++;
				 }
			 }  

		}else
		{
			//step4: 三角形无需简化，可以直接输出
			pTri->changeFlag=false;
		}
		pTri = pTri->pNext;
	}//三角形遍历完毕，边 以及 待处理三角形都已经存储好



}