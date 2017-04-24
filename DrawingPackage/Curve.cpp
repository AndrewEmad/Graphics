#include <Windows.h>
#include <math.h>
#include <algorithm>
#include "Curve.h"

void Curve::DrawHermitCurve(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF c)
{
	double dx1 = (p2.x - p1.x);
	double dy1 = (p2.y - p1.y);
	double dx2 = (p4.x - p3.x);
	double dy2 = (p4.y - p3.y);

	int xcoff[4] = { 2 * p1.x + dx1 - 2 * p3.x + dx2, -3 * p1.x - 2 * dx1 + 3 * p3.x - dx2, dx1, p1.x };
	int ycoff[4] = { 2 * p1.y + dy1 - 2 * p3.y + dy2, -3 * p1.y - 2 * dy1 + 3 * p3.y - dy2, dy1, p1.y };

	for (double t = 0; t < 1; t += 0.001){
		int x = xcoff[0] * t*t*t + xcoff[1] * t*t + xcoff[2] * t + xcoff[3] + 0.5;
		int y = ycoff[0] * t*t*t + ycoff[1] * t*t + ycoff[2] * t + ycoff[3] + 0.5;
		SetPixel(hdc, x, y, c);
	}
}


void Curve::DrawCurve(HDC hdc, COLORREF color){
	int d = -49;
	int y = 0;
	int x = 0;
	for (x = 0; x <= 10; ++x){
		SetPixel(hdc, 150 + x, 150 + y, color);
		SetPixel(hdc, 150 - x, 150 + y, color);
		if (d > 0)
		{
			d += 2 * x - 97; y++;


		}
		else{
			d += 2 * x + 3;
		}
	}
	for (; x < 35; ++y){
		SetPixel(hdc, 150 + x, 150 + y, color);
		SetPixel(hdc, 150 - x, 150 + y, color);
		if (d > 0)
		{
			d += 2 * y - 97;


		}
		else{
			d += 2 * y + 3;
			x++;
		}
	}

}