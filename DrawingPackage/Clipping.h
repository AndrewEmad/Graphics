#ifndef CLIPPING_H
#define CLIPPING_H
#include<Windows.h>
#include"Point.h"
#define CLIPPING_RECTANGLE 23
#define CLIPPING_CIRCLE 24
#define CLIPPING_NONE 25

union OutCode
{
	unsigned All : 4;
	struct
	{
		unsigned left : 1, right : 1, top : 1, bottom : 1;
	};
};
union Code
{
	unsigned all : 1;
	struct
	{
		unsigned outside : 1;
	};
};




class Clipping
{
private:
	static Point VIntersect(double x1,double y1,double x2,double y2,int xEdge);
	static Point HTntersect(double x1, double y1, double x2, double y2, int yEdge);
	static OutCode getOutCode(double x, double y, int xmin, int ymin, int xmax, int ymax);
	
	static Code getCode(double x, double y, int xc, int yc, double r);
	static Point Intersection(double x, double y, int xc, int yc, double r);
public:
	static void PointClippingRectangle(HDC hdc, int x, int y, int xmin, int ymin, int xmax, int ymax, COLORREF color);
	static void LineClippingRectangle(HDC hdc, double xs, double ys, double xe, double ye, int xmin, int ymin, int xmax, int ymax, COLORREF  color);
	
	static void PointClippingCircle(HDC hdc, int x, int y, int xc, int yc, double r, COLORREF c);
	static void LineClippingCircle(HDC hdc, double x1, double y1,double x2,double y2, int xc, int yc, double r, COLORREF c);
};
#endif