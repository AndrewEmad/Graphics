#ifndef CURVE_H
#define CURVE_H

#include <Windows.h>
#include <math.h>
#include <algorithm>

class Curve{

	public:
		void DrawHermitCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF c);
		void DrawCurve(HDC hdc, COLORREF color);
};

#endif