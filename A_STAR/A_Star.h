#pragma once
#include"Map.h"

#include<list>
#include<vector>

struct Cost
{
	unsigned int G_Len;
	unsigned int R_Cos;
};

class A_Star
{
public:
	A_Star() = delete;
	A_Star(Map* map, Point2D start, Point2D tgt);
	~A_Star();

	void Screen();
	list<Point2D> Calc();

private:

	Map* map_;
	int Lowest;
	Point2D st_;
	Point2D tgt_;
	Point2D now_;
	Cost* cost_;

	struct CostMap
	{ 
		Cost cost; 
		Point2D pos;
	};
	std::list<CostMap> CalcableMap;

	bool IsFinish();
	Point2D SerchLowerP2D();
	void SetCost_RCOST();

	int Index();
	int CalcLen();

	int Index(int x, int y);
	int CalcLen(int x , int y);

	int GetMapCost(int x, int y);
};
