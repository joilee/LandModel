#include <iostream>
#include <fstream>
#include <vector>
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
class heightAll
{
public:
	int **p;
	int row,col;
	heightAll(int **pp,int roww,int coll)
	{
		p=pp;
		row = roww;
		col = coll;
	}

};


/*****************************************************************************************
************************读取栅格数据****************************************************
*****************************************************************************************/
vector<heightAll> heightR;/***height数据vector数组***/
void readHeight()
{
	
	string indn = "G:\\xx3Dmap\\heights\\index.txt";



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
		
		int **height = new_Array2D<int>(row,col);
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<col;j++)
			{
				height[i][j] =0;
			}
		}
		heightAll ht(height,row,col);
		
		heightR.push_back(ht);


		char c1,c2;
		int st;
		int no=0,flag=1;
		//int ind ;

		int colt = heightR[hns].col;
		while(FileH.good()&&!FileH.eof())
		{
			FileH>>c1>>c2;
			int tmp = int(c1)*256 +int(c2);
		
			//height.push_back(tmp);
			heightR[hns].p[no/colt][no%colt] = tmp;
		//	height[no/col][no%col] = tmp;
			/*	if (flag&&tmp!=0)
			{
			flag=0;
			st=tmp;
			ind = no;
			break;

			}*/
			//cout<<int(c1)<<" "<<int(c2)<<endl;
			no++;
		}
		cout<<heightR[0].p[1][3744]<<endl;
		//cout<<height[1][3744]<<endl;
		//cout<<ind<<" "<<st<<endl;
	//	cout<<height.size()<<endl;
		FileH.close();
	}
	

}