#ifndef CURVE_H
#define CURVE_H

#include <Windows.h>
#include <math.h>
#include <algorithm>

#define CURVE_HERMIT 14
#define CURVE_BEZIER 15
#define CURVE_CARDINAL_SPLINE 16

class Curve{

	public:
		static void DrawHermitCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF color);
		static void DrawBezierCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF color);
		static void DrawCardinalSpline(HDC hdc, POINT *p, int numOfPoints, double c, COLORREF color);
};

#endif