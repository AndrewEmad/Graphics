#ifndef CLIPPING_H
#define CLIPPING_H
#include<Windows.h>

#define CLIPPING_POINT_RECTANGLE 23
#define CLIPPING_LINE_RECTANGLE 24
#define CLIPPING_POINT_CIRCLE 25
#define CLIPPING_LINE_CIRCLE 26

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