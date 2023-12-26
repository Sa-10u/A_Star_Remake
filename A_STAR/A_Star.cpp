#include "A_Star.h"
#include<cmath>

A_Star::A_Star(Map* map, Point2D start, Point2D tgt):map_(map)
{
	st_.x = start.x + 1;
	st_.y = start.y + 1;

	now_ = st_;

	tgt_.x = tgt.x + 1;
	tgt_.y = tgt.y + 1;

	auto temp_s = map_->real_scale.x * map_->real_scale.y;

	cost_ = new Cost[temp_s];
	auto s = sizeof(cost_[0]) * temp_s;

	memset(cost_, 0, s);

	cost_[Index()].G_Len = CalcLen();
	cost_[Index()].R_Cos = 0;
	Lowest = cost_[Index()].G_Len + cost_[Index()].R_Cos;

	CostMap cosm;
	cosm.cost.G_Len = cost_[Index()].G_Len;
	cosm.cost.R_Cos = cost_[Index()].R_Cos;
	cosm.pos = now_;

	CalcableMap.push_back(cosm);
}

A_Star::~A_Star()
{
}

list<Point2D> A_Star::Calc()
{
	list<Point2D> lists = {};

	while (!IsFinish()) {

		SerchLowerP2D();
		SetCost_RCOST();
		//set path for lists
	}

	return lists;
}

bool A_Star::IsFinish()
{
	return  now_ == tgt_ ? true : false;

}

Point2D A_Star::SerchLowerP2D()
{
	Lowest = INT_MAX;

	for (auto map = CalcableMap.begin(); map != CalcableMap.end(); NULL) {
		auto res = map_->MAP[Index(map->pos.x, map->pos.y)];
		if (map_->MAP[Index(map->pos.x, map->pos.y)] == COMPUTED)
		{
			map = CalcableMap.erase(map);
			continue;
		}
		
		int cost = map->cost.G_Len + map->cost.R_Cos;

		if (Lowest >= cost && GetMapCost(map->pos.x, map->pos.y)) {

			Lowest = cost;
			now_ = map->pos;
		}

		if (map->pos == tgt_)
		{
			now_ = map->pos;
			return now_;
		}


		map++;
	}

	return now_;

}

void A_Star::SetCost_RCOST()
{
	Point2D p;
	p = now_;

	int cos = cost_[Index(now_.x,now_.y)].R_Cos;

	auto Func = [&](int x ,int y)
		{
			if (GetMapCost(x, y) && map_->MAP[Index(x, y)] != COMPUTED)
			{
				cos = cost_[Index()].R_Cos + GetMapCost(x, y);

				cost_[Index(x, y)].R_Cos = cos;
				cost_[Index(x, y)].G_Len = CalcLen(x, y);

				CostMap cosm;
				cosm.cost = cost_[Index(x, y)];
				cosm.pos = p;

				CalcableMap.push_back(cosm);
			}
		};

	p.x = now_.x + 1;	p.y = now_.y;
	Func(p.x, p.y);

	p.x = now_.x ;	p.y = now_.y+1;
	Func(p.x, p.y);

	p.x = now_.x -1;	p.y = now_.y;
	Func(p.x, p.y);

	p.x = now_.x ;	p.y = now_.y-1;
	Func(p.x, p.y);

	p = now_;

	map_->MAP[Index(p.x,p.y)] = COMPUTED;
}

int A_Star::Index()
{
	Point2D pos;
	pos = now_;;
	return map_->GetArrayIndex(pos);
}

int A_Star::CalcLen()
{
	return  (tgt_.x - now_.x) + (tgt_.y - now_.y);
}

int A_Star::Index(int x, int y)
{
	Point2D pos;
	pos.x = x ;
	pos.y = y ;

	return map_->GetArrayIndex(pos);
}

int A_Star::CalcLen(int x, int y)
{
	Point2D pos;
	pos.x = x;
	pos.y = y;

	return  (tgt_.x - pos.x) + (tgt_.y - pos.y);
}

int A_Star::GetMapCost(int x, int y)
{
	switch (map_->MAP[Index(x, y)])
	{
	case BARRIER:return 0;
	
	case COMPUTED: return 0;

	case BLOCK:	return 0;

	case NORMAL:return 1;
	}
}

void A_Star::Screen()
{
	for (auto h = 0u; h < map_->real_scale.y; h++) {
		for (auto w = 0u; w < map_->real_scale.y; w++)
		{
			
			Point2D pos;
			pos.x = w;
			pos.y = h;

			if (pos == st_)	cout << "S ";
			else if (pos == tgt_)	cout << "X ";
			else if (pos == now_)	cout << "V ";

			else if (map_->MAP[map_->GetArrayIndex(pos)] == BARRIER) cout << "* ";
			else if (map_->MAP[map_->GetArrayIndex(pos)] == COMPUTED) cout << cost_[map_->GetArrayIndex(pos)].G_Len + cost_[map_->GetArrayIndex(pos)].R_Cos;
			else cout << "+ ";

			cout << " ";
		}

		cout << endl;
	}
}
