#include "Map.h"
#include<cstring>

Map::Map(Point2D size)
{
	scale = size;
	unsigned int Arr_size = (size.x + ARRAY_BARRIER) * (size.y + ARRAY_BARRIER);

	real_scale.x = size.x + ARRAY_BARRIER;
	real_scale.y = size.y + ARRAY_BARRIER;

	MAP = new type[Arr_size];


	for (auto h = 0u; h < size.y + ARRAY_BARRIER; h++) {
		for (auto w = 0u; w < size.x + ARRAY_BARRIER; w++) {

			if (h != 0 && h != size.y + ARRAY_BARRIER - 1 && w != 0 && w != size.x + ARRAY_BARRIER - 1) MAP[GetArrayIndex(w,h)] = NORMAL;
			
			else
			{
				MAP[GetArrayIndex(w,h)] = BARRIER;
				auto ic = w + (size.y + ARRAY_BARRIER - 1) * h;
			}
		}
	}

	
}

Map::~Map()
{
	delete[] MAP;
}

unsigned int Map::GetArrayIndex(Point2D p)
{
	return p.x + (real_scale.y -1)*p.y;
}

unsigned int Map::GetArrayIndex(int x, int y)
{
	return x + (real_scale.y - 1) * y;
}

void Map::Screen()
{
	for (auto h = 0u; h < real_scale.y; h++ ){
		for (auto w = 0u; w < real_scale.x; w++) {

			cout << MAP[GetArrayIndex(w, h)] << " ";
		}
		cout << endl;
	}
}

bool Point2D::operator==(const Point2D p)
{
	if (this->x == p.x && this->y == p.y)	return true;

	return false;
}
