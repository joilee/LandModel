#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void readVector()
{

	string indn = "G:\\xx3Dmap\\vector\\index.txt";
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
	vector<double> xmins,xmaxs,ymins,ymaxs;
	vector<string> kinds;
	while(Findex.good() && !Findex.eof())
	{
		string hn="";
		double xmin,xmax,ymin,ymax;
		string kind;
		Findex>>hn;
		if (hn!="")
		{
			Findex>>xmin>>xmax>>ymin>>ymax>>kind;
			//cout<<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<" "<<base<<endl;
			Hnames.push_back(hn);
			xmins.push_back(xmin);
			xmaxs.push_back(xmax);
			ymins.push_back(ymin);
			ymaxs.push_back(ymax);
			kinds.push_back(kind);
		}
		
	}
//	cout<<ymaxs[0]<<endl;
	for (int hns=0;hns<Hnames.size();hns++)
	{
		ifstream FileH;
		string tt = headFile +Hnames[hns];
		cout<<tt<<endl;


		FileH.open(tt);

	

	//	while(FileH.good()&&!FileH.eof())
		{

		}
		
	
		FileH.close();
	}
}