//#include "point.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <cmath>

#include "canny.h"
#include "readGrid.h"
#include "vector2.h"
#include "delaunay.h"
#include "IO_obj.h"
#include "Mesh.h"
using namespace std;

void ToTriMeshEar(vector<Pot> poly,vector<Pot> &TriMesh)
//void ToTriMeshEar()
{

	/*vector<Pot> poly;
	vector<Pot> TriMesh;*/
	vector<Pot>::iterator it,it1,it2,endit,t,t1,t2,ittmp;

	/*poly.push_back(Pot(799706.140, 3361756.680,1));
	poly.push_back(Pot(799706.140, 3361751.520,2));
	poly.push_back(Pot(799710.310, 3361744.800,3));
	poly.push_back(Pot(799710.310, 3361751.500,4));*/
	//poly.push_back(Pot(799797.710, 3362151.270,5));
	//poly.push_back(Pot(799812.850, 3362154.540,6));
	//poly.push_back(Pot(799812.850, 3362158.620,7));
	//poly.push_back(Pot(799823.670, 3362158.620,8));
	//poly.push_back(Pot(799826.920, 3362162.020,9));
	//poly.push_back(Pot(799826.920, 3362158.600,10));
	//poly.push_back(Pot(799834.010, 3362158.600,11));
	//poly.push_back(Pot(799834.010, 3362163.680,12));
	//poly.push_back(Pot(799846.260, 3362163.680,13));
	//poly.push_back(Pot(799893.910, 3362173.080,14));
	//poly.push_back(Pot(799893.910, 3362179.590,15));
	//poly.push_back(Pot(799897.740, 3362174.850,16));
	//poly.push_back(Pot(0,0,1));
	//poly.push_back(Pot(0,10,2));
	//poly.push_back(Pot(3,5,3));
	//poly.push_back(Pot(10,10,4));
	//poly.push_back(Pot(10,0,5));
	/**************************************************
	______________判断每个节点的凹凸性_________________
	**************************************************/
//	int spec0num=0;
//	int sepc1num=0;
	endit = poly.end();
	----endit;
	for (it=poly.begin();it!=(endit);it++)
	{
		it1=it;
		it1++;
		it2=it1;
		it2++;
		double x1 = (*it1).x - (*it).x;
		double y1 = (*it1).y - (*it).y;
		double x2 = (*it2).x - (*it1).x;
		double y2 = (*it2).y - (*it1).y;
		/*cout<<x1*y2-x2*y1<<" ";*/
		if (x1*y2-x2*y1>0)
		{
			(*it1).setSpec0();
			//spec0num++;
		}
	}	
	endit = poly.end();
	--endit;
	it1 = endit;
	--endit;
	it = endit;
	it2 = poly.begin();
	{
		double x1 = (*it1).x - (*it).x;
		double y1 = (*it1).y - (*it).y;
		double x2 = (*it2).x - (*it1).x;
		double y2 = (*it2).y - (*it1).y;
		if (x1*y2-x2*y1>0)
		{
			(*it1).setSpec0();
			//spec0num++;
		}
	}

	endit = poly.end();
	--endit;
	it = endit;
	it1 = poly.begin();
	it2 = it1;
	it2++;
	{
		double x1 = (*it1).x - (*it).x;
		double y1 = (*it1).y - (*it).y;
		double x2 = (*it2).x - (*it1).x;
		double y2 = (*it2).y - (*it1).y;
		/*cout<<x1*y2-x2*y1<<endl;*/
		if (x1*y2-x2*y1>0)
		{
			(*it1).setSpec0();
			//spec0num++;
			
		}
	}


	/*if (spec0num>poly.size()-spec0num)
	{
		
		
		for (int i=0;i<poly.size();i++)
		{
			poly[i].spec=!poly[i].spec;
		}

		double xx,yy,zz;
		bool ss;
		int mm;
		for (int i=0;i<poly.size()/2;i++)
		{
			xx = poly[i].x;
			yy = poly[i].y;
			zz = poly[i].z;
			ss = poly[i].spec;
			mm = poly[i].mark;

			poly[i].x = poly[poly.size()-1-i].x;
			poly[i].y = poly[poly.size()-1-i].y;
			poly[i].z = poly[poly.size()-1-i].z;
			poly[i].spec = poly[poly.size()-1-i].spec;
			poly[i].mark = poly[poly.size()-1-i].mark;
			poly[poly.size()-1-i].x = xx;
			poly[poly.size()-1-i].y = yy;
			poly[poly.size()-1-i].z = zz;
			poly[poly.size()-1-i].spec = ss;
			poly[poly.size()-1-i].mark = mm;

		}

	}*/

	
	int index = 0;
	int ind1,ind2,ind3;
	int retrytimes = 0;
	while(poly.size()>3)
	{
		if (retrytimes >40)
		{
			break;
		}
		retrytimes++;
	
		index%=poly.size();
		ind1=index;
		ind2=(index+1)%poly.size();
		ind3=(index+2)%poly.size();
		
		//double k1 = (poly[ind2].y-poly[ind1].y) /( poly[ind2].x-poly[ind1].x);
		//double k2 = (poly[ind3].y-poly[ind1].y) / (poly[ind3].x-poly[ind1].x);
		//double k12=k1/k2;
		//if (k12<0)
		//{
		//	k12 = -k12;
		//}
		////cout<<k12<<endl;
		//if( k12<1.1&&k12>0.9)
		//{
		//	
		////	cout<<index<<endl;
		//	poly.erase(poly.begin()+ind2);
		//	cout<<poly[ind2].mark<<endl;
		//	

		//}
		//else
		{
			bool flag = 0;
			if (poly[ind2].spec==1)
			{
				for (int ii=0;ii<poly.size();ii++)
				{
					if (ii!=ind1&&ii!=ind2&&ii!=ind3)
					{
						flag = IsPotInTriangle3(poly[ind1],poly[ind2],poly[ind3],poly[ii]);
						if (flag==1)
						{
							break;
						}
					}
				}
			}

			if (poly[ind2].spec==1&&flag==0)
			{
				TriMesh.push_back(poly[ind1]);
				TriMesh.push_back(poly[ind3]);
				TriMesh.push_back(poly[ind2]);
				
				double x1 = (poly[ind1]).x - (poly[(ind1+poly.size()-1)%poly.size()]).x;
				double y1 = (poly[ind1]).y - (poly[(ind1+poly.size()-1)%poly.size()]).y;
				double x2 = (poly[ind3]).x - (poly[ind1]).x;
				double y2 = (poly[ind3]).y - (poly[ind1]).y;
				if (x1*y2-x2*y1>0)
				{
					poly[ind1].setSpec0();
				}
				else
				{
					poly[ind1].setSpec1();
				}


				x1 = (poly[ind3]).x - (poly[ind1]).x;
				y1 = (poly[ind3]).y - (poly[ind1]).y;
				x2 = (poly[(ind3+1)%poly.size()]).x - (poly[ind3]).x;
				y2 = (poly[(ind3+1)%poly.size()]).y - (poly[ind3]).y;
				if (x1*y2-x2*y1>0)
				{
					poly[ind3].setSpec0();
				}
				else
				{
					poly[ind3].setSpec1();
				}

				poly.erase(poly.begin()+ind2);

				
			
				
				
			}
			else
			{
				index++;
			}

		}
		
		//cout<<1;

		
	}
	/*for (int i=0;i<TriMesh.size();i++)
	{
		cout<<TriMesh[i].mark<<" ";
	}*/

	
	if (poly.size()==3)
	{
		TriMesh.push_back(poly[0]);
		TriMesh.push_back(poly[2]);
		TriMesh.push_back(poly[1]);
		

	}
	
	poly.clear();
	



}





void ToTriMesh(list<Pot> poly,vector<Pot> &TriMesh)
{
	
	list<Pot>::iterator it,it1,it2,endit,t,t1,t2,ittmp;
	//list<Pot> poly;

	vector<Pot> fPot;

		
	//poly.push_back(Pot(799907.980, 3362177.130,1));
	//poly.push_back(Pot(799922.240, 3362180.300,2));
	//poly.push_back(Pot(799922.240, 3362171.250,3));
	//poly.push_back(Pot(799797.710, 3362142.120,4));
	//poly.push_back(Pot(799797.710, 3362151.270,5));
	//poly.push_back(Pot(799812.850, 3362154.540,6));
	//poly.push_back(Pot(799812.850, 3362158.620,7));
	//poly.push_back(Pot(799823.670, 3362158.620,8));
	//poly.push_back(Pot(799826.920, 3362162.020,9));
	//poly.push_back(Pot(799826.920, 3362158.600,10));
	//poly.push_back(Pot(799834.010, 3362158.600,11));
	//poly.push_back(Pot(799834.010, 3362163.680,12));
	//poly.push_back(Pot(799846.260, 3362163.680,13));
	//poly.push_back(Pot(799893.910, 3362173.080,14));
	//poly.push_back(Pot(799893.910, 3362179.590,15));
	//poly.push_back(Pot(799897.740, 3362174.850,16));
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		


	
	/**************************************************
	__________________插入顶点_________________________
	**************************************************/

	/*poly.push_back(Pot(0,0,1));
	poly.push_back(Pot(10,0,2));
	poly.push_back(Pot(10,10,3));
	poly.push_back(Pot(3,3,4));
	poly.push_back(Pot(0,10,5));
	*/





	/**************************************************
	______________判断每个节点的凹凸性_________________
	**************************************************/

	endit = poly.end();
	----endit;
	for (it=poly.begin();it!=(endit);it++)
	{
		it1=it;
		it1++;
		it2=it1;
		it2++;
		double x1 = (*it1).x - (*it).x;
		double y1 = (*it1).y - (*it).y;
		double x2 = (*it2).x - (*it1).x;
		double y2 = (*it2).y - (*it1).y;
		/*cout<<x1*y2-x2*y1<<" ";*/
		if (x1*y2-x2*y1>0)
		{
			(*it1).setSpec0();
			fPot.push_back(*it1);
		}
	}	
	endit = poly.end();
	--endit;
	it1 = endit;
	--endit;
	it = endit;
	it2 = poly.begin();
	{
		double x1 = (*it1).x - (*it).x;
		double y1 = (*it1).y - (*it).y;
		double x2 = (*it2).x - (*it1).x;
		double y2 = (*it2).y - (*it1).y;
		if (x1*y2-x2*y1>0)
		{
			(*it1).setSpec0();
			fPot.push_back(*it1);
		}
	}

	endit = poly.end();
	--endit;
	it = endit;
	it1 = poly.begin();
	it2 = it1;
	it2++;
	{
		double x1 = (*it1).x - (*it).x;
		double y1 = (*it1).y - (*it).y;
		double x2 = (*it2).x - (*it1).x;
		double y2 = (*it2).y - (*it1).y;
		/*cout<<x1*y2-x2*y1<<endl;*/
		if (x1*y2-x2*y1>0)
		{
			(*it1).setSpec0();
			fPot.push_back(*it1);
			
		}
	}

	


	/*cout<<fPot.size()<<endl;
	for (int i=0;i<fPot.size();i++)
	{
	cout<<fPot[i].mark<<" ";
	}*/
	{
	
		int retrytimes = 0;

		while(poly.size()>3 && fPot.size()>0)
		{
			//cout<<fPot.size()<<endl;
			
			retrytimes++;
			if (retrytimes>20)
			{
				break;
			}
			//step3


			endit = poly.end();
			----endit;

			for (it=poly.begin();it!=(endit);it++)
			{
				it1=it;
				it1++;
				it2=it1;
				it2++;

				if ((*it1).spec==true)
				{
					for (int ii=0;ii<fPot.size();ii++)
					{
					
						bool flag = false;
						flag = IsPotInTriangle3(*it,*it1,*it2,fPot[ii]);
						if (fPot[ii].mark==(*it).mark||fPot[ii].mark==(*it1).mark||fPot[ii].mark==(*it2).mark)
						{
							flag = false;
						}
						if (flag == true)
						{
							goto Step3;
						}
						else
						{
							TriMesh.push_back(*it);
							TriMesh.push_back(*it1);
							TriMesh.push_back(*it2);
						//	cout<<(*it).mark<<" "<<(*it1).mark<<" "<<(*it2).mark<<endl;


							t1= it;
							t=poly.end();

							if (t1==poly.begin())
							{
							
								--t;
							}
							else
							{
								t = t1;
								--t;
							}
							t2 = it2;


							{
								double x1 = (*t1).x - (*t).x;
								double y1 = (*t1).y - (*t).y;
								double x2 = (*t2).x - (*t1).x;
								double y2 = (*t2).y - (*t1).y;
								if (x1*y2-x2*y1>0)
								{
									if ((*t1).spec == 1)
									{
										fPot.push_back(*it);
									}

									(*t1).setSpec0();

								}
								else
								{
									if ((*t1).spec == 0)
									{
										for (vector<Pot>::iterator pit = fPot.begin();pit!=fPot.end();pit++)
										{
											if((*pit).mark==(*t1).mark)
											{
												fPot.erase(pit);
												break;
											}

										}
									}
									(*t1).setSpec1();

								}

							}
						
							poly.erase(it1);
							goto Step4;

						}

					}


				}
	Step3:;




			}
	Step4:;

		}


		if (poly.size()==3)
		{
			it = poly.begin();
			TriMesh.push_back(*it);
			TriMesh.push_back(*(++it));
			TriMesh.push_back(*(++it));
		}
		else
		{
			endit = poly.end();
			----endit;
			for (it=poly.begin();it!=endit;it++)
			{
				ittmp = it;
				TriMesh.push_back(*(poly.begin()));
				TriMesh.push_back(*(++ittmp));
				TriMesh.push_back(*(++ittmp));
			}

		}
		
	}




	
}









void ToOBJ()
{


	vector<GridAll> heightR;/***height数据vector数组***/
	readGrid("G:\\xx3Dmap\\heights\\index.txt",heightR);



	vector<Pot> TriMesh;
	
	ifstream infile;
	infile.open("G:\\xx3DmapResult\\buildVector\\buildings1part");
	ifstream attr;
	attr.open("G:\\xx3DmapResult\\buildVector\\attribute1");


	ofstream outf;
	outf.open("G:\\xx3DmapResult\\buildVector\\buildings1part.obj");
	int tmpi,h;
	string tmps;
	vector<double> high;
	int cnt=0;
	while ( attr.good() && !attr.eof())
	{
		cnt++;
		attr>>tmpi>>tmps>>h;
		high.push_back(h);
	}
	attr.close();

	cnt=0;
	//cout<<high[0];
	int a;
	string b;
	int c;

	vector<Pot> Obj;
	Obj.clear();
	int highValue=-1;

	int num=0;
	while (   infile.good() && !infile.eof())
	{
		num++;
		
		infile>>a>>b>>c;
		highValue++;
		if(b=="Vector"&& !infile.eof())
		{
			vector<Pot> poly,polyh;
			vector<Pot> polyTri;
			polyTri.clear();
			poly.clear();
			polyh.clear();
			for (int i=0;i<c;i++)
			{      
				double x,y;
				infile>>x>>y;
				
				poly.push_back(Pot(x,y,0));
				polyh.push_back(Pot(x,y,0,high[highValue]));

			}

			for (int i=0;i<c-1;i++)
			{
				Obj.push_back(poly[i]);
				Obj.push_back(polyh[i]);
				Obj.push_back(polyh[i+1]);
				Obj.push_back(poly[i]);
				Obj.push_back(polyh[i+1]);
				Obj.push_back(poly[i+1]);


				polyTri.push_back(Pot(poly[i].x,poly[i].y,cnt++,high[highValue]));
			}
		/*	if (num==588)
			{
				goto AA;
			}*/
			ToTriMeshEar(polyTri,TriMesh);

			//for (int ii=0;ii<TriMesh.size();ii++)
			//{
			//	cout<<TriMesh[ii].mark<<" ";
			//}

			//cout<<endl;





		}

	}

	//infile>>a>>b>>c;
	//cout<<a;
//	cout<<TriMesh.size()<<endl;

	double zero = 0.00;

	//cout<<TriMesh.size()<<" "<<Obj.size()<<" "<<Obj.size()%TriMesh.size()<<endl;
	for(int kk=0;kk<TriMesh.size();kk++)
	{
		int xind = (3366156 - TriMesh[kk].y)/5;
		int yind = (TriMesh[kk].x - 792983)/5;	
		int htmp = heightR[0].p[xind][yind];
		outf<<setiosflags(ios::fixed)<<setprecision(3)<<"v "<<TriMesh[kk].x<<" "<<TriMesh[kk].y<<" "<<htmp<<endl;
	}
	for(int kk=0;kk<TriMesh.size();kk++)
	{
		int xind = (3366156 - TriMesh[kk].y)/5;
		int yind = (TriMesh[kk].x - 792983)/5;
		int htmp = heightR[0].p[xind][yind];
	//	htmp = 0;
		outf<<setiosflags(ios::fixed)<<setprecision(3)<<"v "<<TriMesh[kk].x<<" "<<TriMesh[kk].y<<" "<<TriMesh[kk].z+htmp<<endl;
	}
	for (int kk=0;kk<Obj.size();kk++)
	{
		int xind = (3366156 - Obj[kk].y)/5;
		int yind = (Obj[kk].x - 792983)/5;
		int htmp = heightR[0].p[xind][yind];
		//htmp = 0;
		outf<<setiosflags(ios::fixed)<<setprecision(3)<<"v "<<Obj[kk].x<<" "<<Obj[kk].y<<" "<<Obj[kk].z+htmp<<endl;
	}
	int numOfPot = (TriMesh.size()*2+Obj.size())/3;

	for (int i=0;i<TriMesh.size()/3;i++)
	{
		outf<<"f "<< i*3+1<<" "<<i*3+3<<" "<<i*3+2<<endl;
	}

	for (int i=TriMesh.size()/3;i<TriMesh.size()/3*2;i++)
	{
		outf<<"f "<< i*3+1<<" "<<i*3+2<<" "<<i*3+3<<endl;
	}

	for (int i=TriMesh.size()*2/3;i<numOfPot;i++)
	{
		outf<<"f "<< i*3+1<<" "<<i*3+2<<" "<<i*3+3<<endl;
	}
	outf.close();

}

double disP2P(Pot p,Pot q)
{
	double res = (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y)+(p.z-q.z)*(p.z-q.z);
	return sqrt(res);
}



Pot get_Normal(Pot p1,Pot p2,Pot p3)  
{  
	double x1 = p2.x-p1.x;
	double y1 = p2.y-p1.y;
	double z1 = p2.z-p1.z;

	double x2 = p3.x-p2.x;
	double y2 = p3.y-p2.y;
	double z2 = p3.z-p2.z;

	double a = y1*z2 - y2*z1;
	double b = x2*z1 - x1*z2;
	double c = x1*y2 - x2*y1;

	double radix = sqrt(a*a+b*b+c*c);
	
	return Pot(a/radix,b/radix,c/radix);  

} 


//double area[1000][1000];
//Pot Ni[1000][1000];
//double VecNor[1000][1000]={0.0};

/************************************************************************/
/* 根据点分布的九种情况进行处理

入参：row,col,i,j,左上角坐标xmin,ymax
出参：vector<Pot> adjPoints
*/
/************************************************************************/
void getAdjPoint(vector<Pot> &adjPoints,vector<vector<int> >&heights, int row,int col,double stdlen,int i,int j,double xmin,double ymax)
{
	double tmpX=xmin+j*stdlen;
	double tmpY=ymax-i*stdlen;
	//顺时针添加点
	//分为9种情况讨论
	if(i==0&&j==0)//case1: 如果左上角点不存在
	{
		Pot P1=Pot(tmpX+stdlen,tmpY,heights[i][j+1]);
		Pot P2=Pot(tmpX+stdlen,tmpY-stdlen,heights[i+1][j+1]);
		Pot P3=Pot(tmpX,tmpY-stdlen,heights[i+1][j]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
	}else if(i==0&&j<col-1&&j>0) //case2:
	{
		Pot P1=Pot(tmpX+stdlen,tmpY,heights[i][j+1]);
		Pot P2=Pot(tmpX+stdlen,tmpY-stdlen,heights[i+1][j+1]);
		Pot P3=Pot(tmpX,tmpY-stdlen,heights[i+1][j]);
		Pot P4=Pot(tmpX-stdlen,tmpY-stdlen,heights[i+1][j-1]);
		Pot P5=Pot(tmpX-stdlen,tmpY,heights[i][j-1]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
		adjPoints.push_back(P4);
		adjPoints.push_back(P5);

	}else if(i==0&&j==col-1)//case3
	{
		Pot P1=Pot(tmpX,tmpY-stdlen,heights[i+1][j]);
		Pot P2=Pot(tmpX-stdlen,tmpY-stdlen,heights[i+1][j-1]);
		Pot P3=Pot(tmpX-stdlen,tmpY,heights[i][j-1]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
	}else if(0<i&&i<row-1&&j==0)//case4
	{
		Pot P1=Pot(tmpX,tmpY+stdlen,heights[i-1][j]);
		Pot P2=Pot(tmpX+stdlen,tmpY+stdlen,heights[i-1][j+1]);
		Pot P3=Pot(tmpX+stdlen,tmpY,heights[i][j+1]);
		Pot P4=Pot(tmpX+stdlen,tmpY-stdlen,heights[i+1][j+1]);
		Pot P5=Pot(tmpX,tmpY-stdlen,heights[i+1][j]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
		adjPoints.push_back(P4);
		adjPoints.push_back(P5);
	}else if (0<i&&i<row-1&&0<j&&j<col-1)//case5
	{ //从该点的上面一个点计算
		Pot P1=Pot(tmpX,tmpY+stdlen,heights[i-1][j]);
		Pot P2=Pot(tmpX+stdlen,tmpY+stdlen,heights[i-1][j+1]);
		Pot P3=Pot(tmpX+stdlen,tmpY,heights[i][j+1]);
		Pot P4=Pot(tmpX+stdlen,tmpY-stdlen,heights[i+1][j+1]);
		Pot P5=Pot(tmpX,tmpY-stdlen,heights[i+1][j]);
		Pot P6=Pot(tmpX-stdlen,tmpY-stdlen,heights[i+1][j-1]);
	    Pot P7=Pot(tmpX-stdlen,tmpY,heights[i][j-1]);
		Pot P8=Pot(tmpX-stdlen,tmpY+stdlen,heights[i-1][j-1]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
		adjPoints.push_back(P4);
		adjPoints.push_back(P5);
		adjPoints.push_back(P6);
		adjPoints.push_back(P7);
		adjPoints.push_back(P8);
	}else if (0<i&&i<row-1&&j==col-1)//case6
	{
		Pot P1=Pot(tmpX,tmpY-stdlen,heights[i+1][j]);
		Pot P2=Pot(tmpX-stdlen,tmpY-stdlen,heights[i+1][j-1]);
		Pot P3=Pot(tmpX-stdlen,tmpY,heights[i][j-1]);
		Pot P4=Pot(tmpX-stdlen,tmpY+stdlen,heights[i-1][j-1]);
		Pot P5=Pot(tmpX,tmpY+stdlen,heights[i-1][j]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
		adjPoints.push_back(P4);
		adjPoints.push_back(P5);
	}else if(j==0&&i==row-1)//case7
	{
		Pot P1=Pot(tmpX,tmpY+stdlen,heights[i-1][j]);
		Pot P2=Pot(tmpX+stdlen,tmpY+stdlen,heights[i-1][j+1]);
		Pot P3=Pot(tmpX+stdlen,tmpY,heights[i][j+1]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
	}else if (i==row-1&&0<j&&j<col-1)//case8
	{
		Pot P1=Pot(tmpX-stdlen,tmpY,heights[i][j-1]);
		Pot P2=Pot(tmpX-stdlen,tmpY+stdlen,heights[i-1][j-1]);
		Pot P3=Pot(tmpX,tmpY+stdlen,heights[i-1][j]);
		Pot P4=Pot(tmpX+stdlen,tmpY+stdlen,heights[i-1][j+1]);
		Pot P5=Pot(tmpX+stdlen,tmpY,heights[i][j+1]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
		adjPoints.push_back(P4);
		adjPoints.push_back(P5);
	}else if(i==row-1&&j==col-1)//case9
	{
		Pot P1=Pot(tmpX-stdlen,tmpY,heights[i][j-1]);
		Pot P2=Pot(tmpX-stdlen,tmpY+stdlen,heights[i-1][j-1]);
		Pot P3=Pot(tmpX,tmpY+stdlen,heights[i-1][j]);
		adjPoints.push_back(P1);
		adjPoints.push_back(P2);
		adjPoints.push_back(P3);
	}
	
}

/************************************************************************/
/* 得到一个点的法向量   
   入参 原始点  周围点的vector
   返回参数 Pot形式的法向量
*/
/************************************************************************/
Pot GetNormalPoint(Pot src,vector<Pot> adjPoint )
{
	
	int adjSize=adjPoint.size();
	Pot tmpNormal=Pot(0,0,0);
	for(int k=0;k<adjSize-1;k++)
	{
		double per=disP2P(src,adjPoint[k+1])/(disP2P(src,adjPoint[k])+disP2P(src,adjPoint[k+1])+disP2P(adjPoint[k],adjPoint[k+1]));
		Pot Nk=get_Normal(adjPoint[k],src,adjPoint[k+1]);
		tmpNormal.x+=Nk.x*per;
		tmpNormal.y+=Nk.y*per;
		tmpNormal.z+=Nk.z*per;
	}

	if (adjSize==8)
	{
		double per=disP2P(src,adjPoint[0])/(disP2P(src,adjPoint[7])+disP2P(src,adjPoint[0])+disP2P(adjPoint[7],adjPoint[0]));
		Pot Nk=get_Normal(adjPoint[7],src,adjPoint[0]);
		tmpNormal.x+=Nk.x*per;
		tmpNormal.y+=Nk.y*per;
		tmpNormal.z+=Nk.z*per;
	}

	return tmpNormal;
	//		for(int k=0;k<8;k++)
	//		{
	//			double per = (disP2P(Pi,Pj[k+1])) / (disP2P(Pi,Pj[k])+disP2P(Pi,Pj[k+1])+disP2P(Pj[k],Pj[k+1]));
	//			Pot nj = get_Normal(Pi,Pj[k+1],Pj[k]);
	//			//cout<<nj.x<<" "<<nj.y<<" "<<nj.z<<endl;
	//			
	//			Ni[i][j].x+=per * nj.x;
	//			Ni[i][j].y+=per * nj.y;
	//			Ni[i][j].z+=per * nj.z;
	//		}

}



/************************************************************************/
/* 获取栅格中每个点的法向量的水平分量 ,求出九宫格构成8个三角面平均的法向量的θ角
   入参: heights,row col,stdlen,以及左上角顶点坐标，向下减小y，向右增加x
   出参: normals(θ角的形式)

   备注：地图一定是要大于3*3的，不然会出问题。
   added by lg
*/
/************************************************************************/

void GetNormalMatrix(vector<vector<double> >& normals,vector<vector<int> > &heights,int row,int col,double stdlen,double xmin,double ymax)
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
		    // int adjacentNum=0;
			 double tmpX=xmin+j*stdlen;
			 double tmpY=ymax-i*stdlen;
			 double tmpZ=heights[i][j];
			 Pot source=Pot(tmpX,tmpY,tmpZ);//该点的三维坐标
			 vector<Pot> adjPoints;
			 getAdjPoint(adjPoints,heights, row,col,stdlen, i, j,xmin, ymax);//获得邻接点
			 Pot normalPoint= GetNormalPoint(source, adjPoints );//求得该点的法向量
			 double theta=acos(normalPoint.z/normalPoint.getLength());//获得theta值
			 normals[i][j]=theta;
			 
		}
		if(i==200||i==400||i==1000||i==2000||i==3000||i==4000)
		{
		cout<<"处理到第"<<i<<"行"<<endl;
		}
	}
}


/************************************************************************/
/*     读文件 返回图片和图像大小                                        */
/************************************************************************/

void Horizon(string filePath,vector<GridHeight> &heightR,vector<IplImage*>&cannyImg,vector<int>&rowNum,vector<int> &colNum,vector<double>&stdLen,vector<double> &xmin,vector<double>&ymax)
{	 
	//Pot tp = get_Normal(Pot(0,0,0),Pot(1,0,0),Pot(0,1,0));
	//cout<<tp.x<<" "<<tp.y<<" "<<tp.z<<endl;	
	//vector<GridHeight> heightR;/***height数据vector数组***/
	//vector<int> rowNum,colNum;
	//vector<double> stdLen;
	//vector<double> xmin;
	//vector<double> ymax;
	

	//入参：heightPath
	//出参：heightR,rowNum,colNum,stdLen,xmin,ymax 高度数据 行数 列数 格与格之间的距离,左上角顶点的坐标。
	readHeightGrid(filePath,heightR,rowNum,colNum,stdLen,xmin,ymax);

	cout<<"读文件完毕"<<endl;

	//针对每个文件（每张地图）的每个点求法向量
	for(int i=0;i<heightR.size();i++)
	{
		CvSize sizeImage=CvSize(colNum[i],rowNum[i]);
		IplImage *initImage = cvCreateImage(sizeImage, IPL_DEPTH_8U, 1);
		for(int m=0;m<rowNum[i];m++)
		{
			for(int n=0;n<colNum[i];n++)
			{
				int value=abs(255*heightR[i].p[m][n]/256);
				if(value>255)value=255;
				value=(255-value);
				cvSetReal2D(initImage,m,n,value);
			}
		}
		cvShowImage("srcImage", initImage);
			
		
		vector<vector<double> >normalMatrix;
		normalMatrix.resize(rowNum[i],vector<double>(colNum[i]));
		GetNormalMatrix(normalMatrix,heightR[i].p,rowNum[i],colNum[i],stdLen[i],xmin[i], ymax[i]);
		cout<<"取向量完毕"<<endl;
		IplImage *tmpTest=arrayToImage(normalMatrix,rowNum[i],colNum[i]);
		
		//canny算法 生成特征点
		IplImage* cannyTmp = cvCreateImage(cvGetSize(tmpTest),IPL_DEPTH_8U,1);  
		cvCanny(tmpTest, cannyTmp, 20, 300, 3);  
		cvShowImage("cannyImage所有", cannyTmp);
		
		
		cannyImg.push_back(cannyTmp);
		
		//分别对切分的图片 提取特征点
		
		//vector<Vector2<float> > points;
		//map<pair<float,float>,int> axisToID;
		//map<int,int> idToHeight;
		//int id=1;

		//for(int n=0;n<colNum[i];n++)
		//{
		//	for(int m=rowNum[i]-1;m>=0;m--)
		//	{
		//		if(cannyPoint[m][n]!=0)
		//		{
		//			float x=xmin[i]+n*stdLen[i];
		//			float y=ymax[i]-m*stdLen[i];
		//			pair<float,float> p1=make_pair(x,y);
		//			axisToID.insert(make_pair(p1,id));
		//			idToHeight.insert(make_pair(id,heightR[i].p[m][n]));
		//			points.push_back(Vector2<float>(x,y));
		//			id++;
		//		}
		//	}
		//}
		//cout<<"共有"<<points.size()<<"特征点"<<endl;

		//Delaunay triangulation;
		//std::vector<Triangle> triangles = triangulation.triangulate(points);
		//std::cout << triangles.size() << " triangles generated\n";

		//FILE *f = fopen("D:\\obj1.obj", "wt");
		//writeObj(f,triangles,axisToID,idToHeight);
		//fclose(f);
		//cvWaitKey();
		////cvReleaseImage(&tmpTest);
		////cvReleaseImage(&cannyImg);
	}
	cout<<"提取特征点完毕"<<endl;
}

void modelToObj(string objPath,IplImage* cannyImg,GridHeight &heightR,int row,int col,double xmin,double ymax,double stdLen,int area[4])
{
	vector<vector<int> > cannyPoint;
	int nv=0;
	cannyPoint.resize(row,vector<int>(col));
	imageToArray(cannyPoint,cannyImg,row,col,nv);

	MESH meshCTX;
	MESH_PTR pMesh=&meshCTX;
	
	int amount=3;

	int startRow=area[0]-area[2],endRow=area[0]+area[2],startCol=area[1]-area[3],endCol=area[1]+area[3];
	if(startRow<0)startRow=0;
	if(endRow>=row)endRow=row-1;
	if(startCol<0)startCol=0;
	if(endCol>=col)endCol=col-1;

	int totalVer=0;//统计该区域的特征点数量
	for(int n=startCol;n<=endCol;n++)
	{
		for(int m=endRow;m>=startRow;m--)
		{
			if(cannyPoint[m][n]!=0)
			{
				totalVer++;
			}
		}
	}

	InitMesh(pMesh, totalVer);

	for(int n=startCol;n<=endCol;n++)
	{
		for(int m=endRow;m>=startRow;m--)
		{
			if(cannyPoint[m][n]!=0)
			{
				double x=xmin+n*stdLen;
				double y=ymax-m*stdLen;
				double z=heightR.p[m][n];
				((VERTEX2D_PTR)(pMesh->pVerArr+amount))->x = x;
				((VERTEX2D_PTR)(pMesh->pVerArr+amount))->y = y;
				((VERTEX2D_PTR)(pMesh->pVerArr+amount))->z = z;
				amount++;
			}
		}
	}

	cout<<"整张地图共有"<<nv<<"特征点"<<"本区域提取  amount:"<<totalVer<<endl;

	double last_time, this_time;
	last_time = GetTickCount();
	IncrementalDelaunay(pMesh);
	this_time = GetTickCount();
	cout<<"耗时"<<this_time - last_time<<"ms"<<endl;
	FILE *f = fopen(objPath.c_str(), "wt");
	WriteOBJ(f,pMesh);
	fclose(f);
	cvWaitKey();
}