#ifndef CURVE_H
#define CURVE_H

#include <Windows.h>
#include <math.h>
#include <algorithm>

#define CURVE_FIRST_DEGREE 14
#define CURVE_SECOND_DEGREE 15
#define CURVE_HERMIT 16
#define CURVE_BEZIER 17
#define CURVE_CARDINAL_SPLINE 18

class Curve{

	public:
		static void DrawFirstDegreeCurve(HDC hdc, POINT ps, POINT pe, COLORREF c);
		static void DrawSecondDegreeCurve(HDC hdc, POINT p1, POINT p2, POINT p3, COLORREF c);
		static void DrawHermitCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF color);
		static void DrawBezierCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF color);
		static void DrawCardinalSpline(HDC hdc, POINT *p, int numOfPoints, double c, COLORREF color);
};

#endif