#ifndef CURVE_H
#define CURVE_H

#include <Windows.h>
#include <math.h>
#include <algorithm>

#define CURVE_HERMIT 13
#define CURVE_CADINAL_SPLINES 14

class Curve{

	public:
		void DrawHermitCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF c);
};

#endif