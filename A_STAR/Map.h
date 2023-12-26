#pragma once
#include<iostream>
using namespace std;

constexpr int ARRAY_BARRIER = 2;

struct Point2D
{
	int x;
	int y;

	bool operator ==(const Point2D p);
};

enum type
{
	BARRIER = -3,
	COMPUTED = -2,
	BLOCK = -1,
	NORMAL,
};

struct Map
{
	type* MAP;
	Point2D scale;
	Point2D real_scale;

	Map() = delete;

	Map(Point2D size);
	~Map();
	unsigned int GetArrayIndex(Point2D p);
	unsigned int GetArrayIndex(int x, int y);

	void Screen();
};