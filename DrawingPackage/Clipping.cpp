#include<Windows.h>
#include<math.h>
#include"Clipping.h"
#include<"Line.h"
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
struct Point
{
	double x, y;
	Point()
	{};
	Point(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
};
void Clipping::PointClippingRectangle(HDC hdc,int x, int y, int xmin, int ymin, int xmax, int ymax, COLORREF color)
{
	if (x >= xmin&&x <= xmax&&y >= ymin&&y <= ymax)
	{
		SetPixel(hdc, x, y, color);
	}
}
Point Clipping::VIntersect(double x1, double y1, double x2, double y2, int xEdge)
{
	Point point;
	point.x = xEdge;
	point.y = y1 + (point.x - x1)*(y2 - y1) / (x2 - x1);
	return point;
}
Point Clipping::HTntersect(double x1, double y1, double x2, double y2, int yEdge)
{
	Point point;
	point.y = yEdge;
	point.x = x1 + (point.y - y1)*(x2 - x1) / (y2 - y1);
	return point;
}
OutCode Clipping::getOutCode(double x, double y, int xmin, int ymin, int xmax, int ymax)
{
	OutCode result;
	result.All = 0;
	if (x < xmin)
	{
		result.left = 1;
	}
	else if (x>xmax)
	{
		result.right = 1;
	}
	if (y < ymin)
	{
		result.top = 1;
	}
	else if (y>ymax)
	{
		result.bottom = 1;
	}
	return result;
}
void Clipping::LineClippingRectangle(HDC hdc, double xs, double ys, double xe, double ye, int xmin, int ymin, int xmax, int ymax, COLORREF  color)
{
	OutCode outCode1 = getOutCode(xs, ys, xmin, ymin, xmax, ymax);
	OutCode outCode2 = getOutCode(xe, ye, xmin, ymin, xmax, ymax);
	while ((outCode1.All || outCode2.All) && !(outCode1.All&outCode2.All))
	{
		
		if (outCode1.All)
		{
			Point p;
			if (outCode1.left)
			{
				p = VIntersect(xs, ys, xe, ye, xmin);
			}
			else if (outCode1.right)
			{
				p = VIntersect(xs, ys, xe, ye, xmax);
			}
			else if (outCode1.top)
			{
				p = HTntersect(xs, ys, xe, ye, ymin);
			}
			else if (outCode1.bottom)
			{
				p = HTntersect(xs, ys, xe, ye, ymax);
			}
			xs = p.x;
			ys = p.y; 
			outCode1 = getOutCode(xs, ys, xmin, ymin, xmax, ymax);
		}
		else if (outCode2.All)
		{
			Point p;
			if (outCode2.left)
			{
				p = VIntersect(xs, ys, xe, ye, xmin);
			}
			else if (outCode2.right)
			{
				p = VIntersect(xs, ys, xe, ye, xmax);
			}
			else if (outCode2.top)
			{
				p = HTntersect(xs, ys, xe, ye, ymin);
			}
			else if (outCode2.bottom)
			{
				p = HTntersect(xs, ys, xe, ye, ymax);
			}
			xe = p.x;
			ye = p.y;
			outCode2= getOutCode(xe, ye, xmin, ymin, xmax, ymax);
		}
	}
	if (!outCode1.All&!outCode2.All)
	{
		DrawDDA(hdc, xs, ys, xe, ye, color);
	}
}

// clipping point for a circle window
void Clipping::PointClippingCircle(HDC hdc, int x, int y, int xc, int yc, double r, COLORREF color)
{
	double result = sqrt((pow((x - xc)*1.0, 2) + pow((y - yc)*1.0, 2)));
	if (result <= r)
	{
		SetPixel(hdc, x, y, color);

	}
}
Code Clipping::getCode(double x, double y, int xc, int yc, double r)
{
	Code result;
	double dist = sqrt((x - xc)*(x - xc) + (y - yc)*(y - yc));
	result.all = 0;
	if (dist > r)
	{
		result.outside = 1;
	}
	return result;
}
Point Clipping::Intersection(double x, double y, int xc, int yc, double r)
{
	Point point;
	double dist = sqrt(pow(x - xc, 2) + pow(y - yc, 2));
	if (dist <= r)
	{
		point.x = x;
		point.y = y;
	}
	else
	{
		double slope = (y - yc) / (x - xc);
		point.x = xc + r*cos(slope);
		point.y = yc + r*sin(slope);
	}
	return point;
}
void Clipping::LineClippingCircle(HDC hdc, double xs, double ys, double xe, double ye, int xc, int yc, double r, COLORREF color)
{
	Code outCode1 = getCode(xs, ys, xc, yc, r);
	Code outCode2 = getCode(xe, ye, xc, yc, r);
	while ((outCode1.all || outCode2.all) && !(outCode1.all&outCode2.all))
	{
		if (outCode1.all)
		{
			Point point;
			point = Intersection(xs, ys, xc, yc, r);
			xs = point.x;
			ys = point.y;
			outCode1 = getCode(xs, ys, xc, yc, r);
		}
		else if (outCode2.all)
		{
			Point point;
			point = Intersection(xe, ye, xc, yc, r);
			xe = point.x;
			ye = point.y;
			outCode2 = getCode(xe, ye, xc, yc, r);
		}
	}
	if (!outCode1.all&!outCode2.all)
	{
		DrawDDA(hdc, xs, ys, xe, ye, color);
	}
}
/*Code Clipping::getCode(double x, double y, int xc, int yc, double r)
{
	Code result;
	result.all = 0;
	double res = sqrt((x - xc)*(x - xc) + (y - yc)*(y - yc));
	if (res > r)
	{
		result.outside = 1;
	}
	return result;
}
Point Clipping::Intersection(double x, double y, int xc, int yc, double r)
{
	double slope = (y - yc) / (x - xc);
	Point point;
	point.x = xc + r*1.0/sqrt(1 / (slope*slope));
	point.y = yc + r*1.0 / sqrt(1 + 1 / (slope*slope));
	return point;
}
void Clipping::LineClippingCircle(HDC hdc,double xs, double ys, double xe, double ye, int xc, int yc, double r, COLORREF color)
{
	Code outCode1 = getCode(xs, ys, xc, yc, r);
	Code outCode2 = getCode(xe, ye, xc, yc, r);
	while ((outCode1.all || outCode2.all) && !(outCode1.all&outCode2.all))
	{
		if (outCode1.all)
		{
			Point point;
			if (outCode1.outside)
			{
				point=Intersection(xs, ys, xc, yc, r);
			}
			xs = point.x;
			ys = point.y;
			outCode1 = getCode(xs,ys, xc, yc, r);
		}
		else if (outCode2.all)
		{
			Point point;
			if (outCode2.outside)
			{
				point = Intersection(xe, ye, xc, yc, r);
			}
			xe = point.x;
			ye = point.y;
			outCode2 = getCode(xe, ye, xc, yc, r);
		}
	}
	if (!outCode1.all&!outCode2.all)
	{
		DrawDDA(hdc, xs, ys, xe, ye, color);
	}
}*/