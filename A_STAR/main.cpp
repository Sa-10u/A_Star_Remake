#include"A_Star.h"

int main()
{
	Point2D s;
	s.x = 8; s.y = 8;

	Point2D st;
	st.x = 1; st.y = 1;

	Point2D tgt;
	tgt.x = 7; tgt.y = 7;

	Map* m = new Map(s);
	A_Star ast(m, st, tgt);

	ast.Calc();

	ast.Screen();

	delete m;
}