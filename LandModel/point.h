#include <math.h>
#ifndef POT 
#define POT
class Pot{
public:
	double x;
	double y;
	double z;
	
	bool spec;//凹凸性，凸1，凹0
	int mark;//顶点编号
	Pot(double xx,double yy)
	{
		x =xx;
		y =yy;
		spec = true;
	}
	Pot(double xx,double yy,double zz)
	{
		x =xx;
		y =yy;
		z =zz;
	}
	Pot()
	{
		x=0;y=0;z=0;
	}
	Pot(double xx,double yy,int mm,double zz)
	{
		x =xx;
		y =yy;
		z =zz;
		mark = mm;
		spec = true;
	}

	double getLength()
	{
	return sqrt(x*x+y*y+z*z);
	}
	void setSpec0()
	{
		spec = false;
	}
	void setSpec1()
	{
		spec = true;
	}

	//二维向量叉乘, 叉乘的结果其实是向量，方向垂直于两个向量组成的平面，这里我们只需要其大小和方向
	double CrossProduct(const Pot vec)
	{
		return x*vec.y - y*vec.x;
	}

	double DotProduct(const Pot vec)
	{
		return x* vec.x+ y * vec.y;
	}

	//二维向量减法
	Pot Minus(const Pot vec) const
	{
		return Pot(x- vec.x, y - vec.y);
	}

	//判断点M,N是否在直线AB的同一侧
	static bool IsPotAtSameSideOfLine(const Pot &PotM, const Pot &PotN, const Pot &PotA, const Pot &PotB)
	{
		Pot AB = PotB.Minus(PotA);
		Pot AM = PotM.Minus(PotA);
		Pot AN = PotN.Minus(PotA);

		//等于0时表示某个点在直线上
		return AB.CrossProduct(AM) * AB.CrossProduct(AN) >= 0;
	}
};
#endif

double ComputeTriangleArea(Pot PotA_, Pot PotB_, Pot PotC_)
{
	//依据两个向量的叉乘来计算，可参考http://blog.csdn.net/zxj1988/article/details/6260576
	Pot AB = PotB_.Minus(PotA_);
	Pot BC = PotC_.Minus(PotB_);
	return fabs(AB.CrossProduct(BC) / 2.0);
}



bool IsPotInTriangle3(Pot PotA_, Pot PotB_, Pot PotC_,const Pot PotP)
{
	Pot AB = PotB_.Minus(PotA_);
	Pot AC = PotC_.Minus(PotA_);
	Pot AP = PotP.Minus(PotA_);
	double dot_ac_ac = AC.DotProduct(AC);
	double dot_ac_ab = AC.DotProduct(AB);
	double dot_ac_ap = AC.DotProduct(AP);
	double dot_ab_ab = AB.DotProduct(AB);
	double dot_ab_ap = AB.DotProduct(AP);

	double tmp = 1.0 / (dot_ac_ac * dot_ab_ab - dot_ac_ab * dot_ac_ab);

	double u = (dot_ab_ab * dot_ac_ap - dot_ac_ab * dot_ab_ap) * tmp;
	if(u < 0 || u > 1)
		return false;
	double v = (dot_ac_ac * dot_ab_ap - dot_ac_ab * dot_ac_ap) * tmp;
	if(v < 0 || v > 1)
		return false;

	return u + v <= 1;
}

