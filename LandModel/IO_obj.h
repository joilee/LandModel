#include "delaunay.h"
#include "Mesh.h"
#include <map>
using namespace std;


/************************************************************************/
/* 将三角形转成obj                                                      */
/************************************************************************/
void writeObj(FILE *f,vector<Triangle> &tri,map<pair<float,float>,int> &axisToID,map<int,int> &idToHeight)
{
	map<pair<float,float>,int>::iterator it=axisToID.begin();
	for(;it!=axisToID.end();it++)
	{
		int id=it->second;
		double z=idToHeight[id];
		//double z=0;
		double x=it->first.first;
		double y=it->first.second;
		fprintf(f, "v %f %f %f\n", x,y,z);

	}
	for(vector<Triangle>::iterator itTri=tri.begin();itTri!=tri.end();itTri++)
	{
		int id1,id2,id3;
		float x1=itTri->p1.x;
		float y1=itTri->p1.y;
		float z1;
		map<pair<float,float>,int>::iterator itId1=axisToID.find(make_pair(x1,y1));
		if(itId1!=axisToID.end())
		{
		 id1=itId1->second;
		 z1=idToHeight[id1];
		}

		float x2=itTri->p2.x;
		float y2=itTri->p2.y;
		float z2;
		map<pair<float,float>,int>::iterator itId2=axisToID.find(make_pair(x2,y2));
		if(itId2!=axisToID.end())
		{
			id2=itId2->second;
			z2=idToHeight[id2];
		}

		float x3=itTri->p3.x;
		float y3=itTri->p3.y;
		float z3;
		map<pair<float,float>,int>::iterator itId3=axisToID.find(make_pair(x3,y3));
		if(itId3!=axisToID.end())
		{
			id3=itId3->second;
			z3=idToHeight[id3];
		}

		double vx1,vy1,vz1,vx2,vy2,vz2;
		vx1=x2-x1; vy1=y2-y1; vz1=z2-z1;
		vx2=x3-x1; vy2=y3-y1; vz2=z3-z1;

		if((vy1*vz2==vz1*vy2)&&(vz1*vx2==vx1*vz2)&&(vx1*vy2==vy1*vx2))
		{
			cout<<"有三点共线"<<endl;
		}else
		{
			fprintf(f, "f %d %d %d\n", id1, id2, id3); 
		}
		
		
	}

	
}


void WriteOBJ(FILE *f, MESH_PTR pMesh)
{
	//输出点
	VERTEX2D_PTR pVtx=pMesh->pVerArr;
	int numV=pMesh->vertex_num;
	for(int i=3;i<numV+3;i++)
	{
		double x,y,z;
		x=((VERTEX2D_PTR)(pMesh->pVerArr+i))->x;
		y=((VERTEX2D_PTR)(pMesh->pVerArr+i))->y;
		z=((VERTEX2D_PTR)(pMesh->pVerArr+i))->z;
		fprintf(f, "v %f %f %f\n", x,y,z);
	}


	//输出三角形
	int tri_index = 0;
	TRIANGLE_PTR pTri = pMesh->pTriArr;
	int* pi;
	while(pTri != NULL)	
	{
		tri_index++;
		int id[3];
		pi = &(pTri->i1);
		for (int j=0; j<3; j++)	
		{	
			id[j] = *pi++;	
			id[j]=id[j]-2;

		}
		fprintf(f, "f %d %d %d\n", id[0], id[1], id[2]); 
		pTri = pTri->pNext;
	}
	UnInitMesh(pMesh);
}