#ifndef LINE_H
#define LINE_H

#include <Windows.h>
#include <math.h>
#include <algorithm>

class Line{
	
	public:
		void DrawParametric(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color);
		void DrawDirect(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color);
		void DrawDDA(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color);
		void DrawMidPoint(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color);

};

#endif