#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <iomanip>
using namespace std;
class Pot2{
public:
	double x;
	double y;
	//double z;
	Pot2(double xx,double yy)
	{
		x =xx;
		y =yy;
	//	z =zz;
	}
};
vector<Pot2> Arr2,Arr2T,Arr2R;
vector<int> attrsz;
double Base = 3.0;
double BaseUnit = Base * Base;
//vector<int> Arr2OfLen;
void buildingSim()
{

	int testlen = 100;


	ifstream infile;
	infile.open("G:\\xx3Dmap\\buildVector\\buildings1");
//	ifstream attr;
//	attr.open("attribute1");



	ofstream outf;
	outf.open("G:\\xx3DmapResult\\buildVector\\buildings1part");

	ofstream outf1;
	outf1.open("G:\\xx3DmapResult\\buildVector\\buildings1part_relative");

	int a,c;
	string b;

	int cnt=0;
	int no = 0;
	int xuhao =2;
	while (   infile.good() && !infile.eof())
	{
		cnt++;
		b=="";
		infile>>a>>b>>c;
		if(b=="Vector"&& !infile.eof() )
		{

			Arr2.clear();
			Arr2T.clear();
			Arr2R.clear();

			for (int i=0;i<c;i++)
			{
				double x,y;
				infile>>x>>y;
				if(i!=c-1)
				{
					Arr2.push_back(Pot2(x,y));
				}
				

			}
			double xt,yt;
			xt = Arr2[0].x;
			yt = Arr2[0].y;
		
		
			Arr2T.push_back(Pot2(xt,yt));
			
			for(int i=1;i<c-1;i++)
			{
				if ((Arr2[i].x-xt)*(Arr2[i].x-xt)+(Arr2[i].y-yt)*(Arr2[i].y-yt)  >BaseUnit)
				{
				/****将横坐标或纵坐标比较接近的归约到一起*****/
					if ((Arr2[i].x-xt)*(Arr2[i].x-xt) >9)
					{
						xt = Arr2[i].x;
					}
					
					if ((Arr2[i].y-yt)*(Arr2[i].y-yt) >9)
					{
						yt = Arr2[i].y;
					}
					
					
					
				//	cout<<xt<<" "<<yt<<endl;
					Arr2T.push_back(Pot2(xt,yt));
				}
			}
			int st= Arr2T.size()-1;
			if ( (Arr2T[st].x-Arr2T[0].x)*(Arr2T[st].x-Arr2T[0].x) +(Arr2T[st].y-Arr2T[0].y)*(Arr2T[st].y-Arr2T[0].y) < BaseUnit)
			{
				Arr2T.pop_back();
			}
			Arr2T.push_back(Arr2[0]);
			int len = Arr2T.size();

			/********************************************* 
			*****计算点与两侧点角度，若太小则删除*********
			*********角度在30度到150度之间****************
			*********************************************/
			Arr2R.push_back(Arr2T[0]);
			for (int i=1;i<len-1;i++)
			{
				Pot2 AB(Arr2T[i-1].x-Arr2T[i].x,Arr2T[i-1].y-Arr2T[i].y);
				Pot2 AC(Arr2T[i+1].x-Arr2T[i].x,Arr2T[i+1].y-Arr2T[i].y);

				double ABAC = AB.x *AC.x +AB.y*AC.y;
				ABAC = ABAC *ABAC;

				double ABL = AB.x * AB.x + AB.y * AB.y;
				double ACL = AC.x * AC.x + AC.y * AC.y;

				
				double cos2BAC = ABAC / (ABL*ACL);
			
				if (cos2BAC < 0.75)
				{
					Arr2R.push_back(Arr2T[i]);
				}
				

			}
			Arr2R.push_back(Arr2T[0]);



			if (Arr2R.size()>3)
			{
				outf<<setw(5)<<setfill(' ')<<xuhao<<"          "<<b<<"                             "<<Arr2R.size()<<endl;
				outf1<<setw(5)<<setfill(' ')<<xuhao<<"          "<<b<<"                             "<<Arr2T.size()<<endl;
				
				xuhao++;
				for (int i=0;i<Arr2R.size();i++)
				{
					outf<<setiosflags(ios::fixed)<<setprecision(3)<<Arr2R[i].x<<" "<<Arr2R[i].y<<endl;
					outf1<<setiosflags(ios::fixed)<<setprecision(3)<<Arr2T[i].x-792983.117<<" "<<Arr2T[i].y-3340226.127<<endl;
				}
			}
		


		}



		
		
	}




	outf.close();
	outf1.close();


}