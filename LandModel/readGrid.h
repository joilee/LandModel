#ifndef   RDGRID_H 
#define   RDGRID_H  
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "point.h"

//#include "array2D.h"

using namespace std;

/*******动态申请二维数组***********/
template <typename T>
T** new_Array2D(int row, int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	//先申请内存，其中sizeof(T*) * row表示存放row个行指针
	T **arr = (T **) malloc(point_size * row + size * row * col);
	if (arr != NULL)
	{	
		T *head = (T*)((int)arr + point_size * row);
		for (int i = 0; i < row; ++i)
		{
			arr[i] =  (T*)((int)head + i * col * size);
			for (int j = 0; j < col; ++j)
				new (&arr[i][j]) T;
		}
	}
	return (T**)arr;
}
/***********释放二维数组*************/
template <typename T>
void delete_Array2D(T **arr, int row, int col)
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			arr[i][j].~T();
	if (arr != NULL)
		free((void**)arr);
}

//vector<int> height;
class GridAll
{
public:
	int **p;
	int row,col;
	GridAll(int **pp,int roww,int coll)
	{
		p=pp;
		row = roww;
		col = coll;
	}

};
class GridHeight
{
public:
	vector< vector<int> > p;
	int row,col;
	GridHeight(vector< vector<int> > pp,int roww,int coll)
	{
		p=pp;
		row = roww;
		col = coll;
	}

};
void readGrid(string index,vector<GridAll> &gridR )
{
	string indn = index;
	ifstream Findex;
	int addrOfIndn=0;
	for (int i=indn.size()-1;i>=0;i--)
	{
		if (indn[i]=='\\')
		{
			addrOfIndn =i;
			break;
		}
	}

	string headFile = indn.substr(0,addrOfIndn+1);
	Findex.open(indn);
	
	vector<string> Hnames;
	vector<double> xmins,xmaxs,ymins,ymaxs,bases;
	while(Findex.good() && !Findex.eof())
	{
		string hn="";
		double xmin,xmax,ymin,ymax,base;
		Findex>>hn;
		if (hn!="")
		{
			Findex>>xmin>>xmax>>ymin>>ymax>>base;
			//cout<<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<" "<<base<<endl;
			Hnames.push_back(hn);
			xmins.push_back(xmin);
			xmaxs.push_back(xmax);
			ymins.push_back(ymin);
			ymaxs.push_back(ymax);
			bases.push_back(base);
		}
		
	}
//	cout<<ymaxs[0]<<endl;
	for (int hns=0;hns<Hnames.size();hns++)
	{
		ifstream FileH;
		string tt = headFile +Hnames[hns];
		//cout<<tt<<endl;



		FileH.open(tt,ios::binary);

		int row = 5297;
		row = (ymaxs[hns]-ymins[hns])/bases[hns];
		
		int col = 4613;
		col = (xmaxs[hns]-xmins[hns])/bases[hns];
		row++;
		col++;
		int **height = new_Array2D<int>(row,col);
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<col;j++)
			{
				height[i][j] =0;
			}
		}
		GridAll gt(height,row,col);
		
		gridR.push_back(gt);


		char c1,c2;
		char c3[2];
		const int Nc=80;
	//	char cstr[Nc];
		 
		
		int st;
		int no=0,flag=1;

		int num=0;

		int colt = gridR[hns].col;

		while(FileH.good()&&!FileH.eof())
		{
			//FileH>>c1>>c2;
			FileH.read(c3,2);
			c1= c3[0];
			c2= c3[1];
			
			int tmp = int(c1)*256 +int(c2);
			gridR[hns].p[no/colt][no%colt] = tmp;

			no++;
		}
		

		FileH.close();
	}
	
}






/*****************************************************************************************
************************读取高度栅格数据****************************************************
***************************modified BY LG**************************************************************/

/* 根据路径，读取所有的文件*/
void readHeightGrid(string index,vector<GridHeight> &gridR,vector<int>&rowNumber,vector<int> &colNumber,vector<double>&bases,vector<double> &xmins,vector<double>&ymaxs )
{

	//ofstream htbs;
	//htbs.open("G:\\xx3DmapResult\\buildVector\\htbs.txt");
	
	//string indn = "G:\\xx3Dmap\\heights\\index.txt";
	string indn = index;


	ifstream Findex;
	int addrOfIndn=0;
	for (int i=indn.size()-1;i>=0;i--)
	{
		if (indn[i]=='\\')
		{
			addrOfIndn =i;
			break;
		}
	}

	string headFile = indn.substr(0,addrOfIndn+1);

	Findex.open(indn);
	
	vector<string> Hnames;
	vector<double> xmaxs,ymins;
	while(Findex.good() && !Findex.eof())
	{
		string hn="";
		double xmin,xmax,ymin,ymax,base;
		Findex>>hn;
		if (hn!="")
		{
			Findex>>xmin>>xmax>>ymin>>ymax>>base;
			//cout<<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<" "<<base<<endl;
			Hnames.push_back(hn);
			xmins.push_back(xmin);
			xmaxs.push_back(xmax);
			ymins.push_back(ymin);
			ymaxs.push_back(ymax);
			bases.push_back(base);
		}
		
	}
//	cout<<ymaxs[0]<<endl;

	/************************************************************************/
	/*       针对每个文件单独处理，获取高度值和行数列数                         */
	/************************************************************************/

	for (int hns=0;hns<Hnames.size();hns++)
	{
		ifstream FileH;
		string tt = headFile +Hnames[hns];
		//cout<<tt<<endl;

		FileH.open(tt,ios::binary);

		//获取行列值
		int row = 0;
		row = int((ymaxs[hns]-ymins[hns])/bases[hns]);
		
		int col = 0;
		col = int((xmaxs[hns]-xmins[hns])/bases[hns]);
		row++;
		col++;


		//int **height = new_Array2D<int>(row,col);
		vector<vector<int> >height ;
		height.resize(row,vector<int>(col));
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<col;j++)
			{
				height[i][j]=0;
			}
		}
		GridHeight gt(height,row,col);

		//存储三个值
		gridR.push_back(gt);
		rowNumber.push_back(row);
		colNumber.push_back(col);

		char c1,c2;
		char c3[2];
		const int Nc=80;
		//char cstr[Nc];
		// 	
		//int st;
		int no=0,flag=1;

		int num=0;
		int colt = gridR[hns].col;

		while(FileH.good()&&!FileH.eof())
		{
			FileH.read(c3,2);
			c1= c3[0];
			c2= c3[1];				
			int tmp = int(c1)*256 +int(c2);
			gridR[hns].p[no/colt][no%colt] = tmp;
			no++;
		}
		FileH.close();
	}
	
//AB:htbs.close();
	//cout<<"OO";

}

vector<GridAll> gridR;/***height数据vector数组***/

class PotIntxy{
public:
	int x;
	int y;
	PotIntxy(int xx,int yy)
	{
		x=xx;
		y=yy;
	}
	PotIntxy(const PotIntxy &p)
	{
		x = p.x;
		y = p.y;
	}
};

int cmp( PotIntxy a, PotIntxy b)
{
	if (a.x<b.x)
	{
		return 1;
	}
	else if (a.x>b.x)
	{
		return 0;
	}
	else
	{
		return a.y<b.y;
	
	}
}

int Xdev[4] = {-1,0,0,1};
int Ydev[4] = {0,-1,1,0};

int vv=0;
void juhe()
{
	//vector<PotIntxy> P;
	//P.push_back(PotIntxy(1,1));
	//P.push_back(PotIntxy(3,1));
	//P.push_back(PotIntxy(2,2));
	//P.push_back(PotIntxy(2,4));

	//sort(P.begin(),P.end(),cmp);

	/*for(int mm=0;mm<P.size();mm++)
	{
		cout<<P[mm].x<<" "<<P[mm].y<<" ";
	}
	cout<<endl;*/
	readGrid("G:\\xx3Dmap\\buildings\\index.txt",gridR);
	cout<<"load over"<<endl;

	//cout<<gridR[0].p[14][3705]<<endl;
	//cout<<gridR[0].p[13][3705]<<endl;
	//cout<<gridR[0].p[14][3704]<<endl;
	//cout<<gridR[0].p[14][3706]<<endl;
	//cout<<gridR[0].p[15][3705]<<endl;
	int cnt=0;

	for (int i=0;i<gridR[0].row;i++)
	{
		for (int j=0;j<gridR[0].col;j++)
		{
			if (gridR[0].p[i][j]!=0)
			{
				vv++;
				//cout<<i<<" "<<j<<" ok"<<endl;
				queue<PotIntxy> Origs;
				Origs.empty();
				vector<PotIntxy> Psets;
				Psets.clear();
			
				Psets.push_back(PotIntxy(i,j));//存结果点
				Origs.push(PotIntxy(i,j));//存递归遍历点
				gridR[0].p[i][j]=0;


				//递归算法
				int topX,topY;
				while(Origs.size()>0)
				{
				//	PotIntxy topP(Origs.front().x,Origs.front().y);
					topX = Origs.front().x;
					
					topY = Origs.front().y;
					//gridR[0].p[topX][topY]=0;
					Origs.pop();
					for (int mm=0;mm<4;mm++)
					{
						if (Xdev[mm]+topX>=0&&Xdev[mm]+topX<gridR[0].row&&Ydev[mm]+topY>=0&&Ydev[mm]+topY<gridR[0].col)
						{
							if (gridR[0].p[Xdev[mm]+topX][Ydev[mm]+topY]!=0)
							{
								gridR[0].p[Xdev[mm]+topX][Ydev[mm]+topY]=0;
								Origs.push(PotIntxy(Xdev[mm]+topX,Ydev[mm]+topY));
								Psets.push_back(PotIntxy(Xdev[mm]+topX,Ydev[mm]+topY));
							}
						}
						
					}
					
				}
				sort(Psets.begin(),Psets.end(),cmp);
				
				for(int mm=0;mm<Psets.size();mm++)
				{
					cout<<Psets[mm].x<<" "<<Psets[mm].y<<" ";
				}


				cout<<endl;
			//	cout<<Psets.size();

				if(vv==5)
				{
					goto A;
				}
				


	
				
			}
		}
	}
	//cout<<gridR[0].p[1][3744]<<endl;
	A:;
}

#endif
