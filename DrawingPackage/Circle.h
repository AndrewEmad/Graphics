#ifndef CIRCLE_H
#define CIRCLE_H

#include <Windows.h>
#include <math.h>
#include <algorithm>

#define CIRCLE_DIRECT_CARTESIAN 9
#define CIRCLE_DIRECT_POLAR 10
#define CIRCLE_ITERATIVE_POLAR 11
#define CIRCLE_MIDPOINT 12

class Circle{
	private:
		void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color);

		int distance(int xs, int ys, int xe, int ye);


	public:
		void DrawDirectCartesian(HDC hdc, int xc, int yc, int r, COLORREF color);

		void DrawDirectPolar(HDC hdc, int xc, int yc, int r, COLORREF color);

		void DrawIterativePolar(HDC hdc, int xc, int yc, int r, COLORREF color);

		void DrawMidPoint(HDC hdc, int xc, int yc, int r, COLORREF color);

};

#endif