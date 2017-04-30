#ifndef SESSION_H
#define SESSION_H
#include<vector>
#include<Windows.h>
#include"Point.h"


struct Command{
	int Algorithm;
	COLORREF Color;
	int numberOfPoints;
	Point *points;
	
	Command(int alg, COLORREF clr, int nop ,Point*p){
		Algorithm = alg;
		Color = clr;
		numberOfPoints = nop;
		points = new Point[numberOfPoints];
		for (int i = 0; i < numberOfPoints; ++i){
			points[i].x = p[i].x;
			points[i].y = p[i].y;
		}
	}
};

class Session{
	private:
		static COLORREF BG_Color;
		static COLORREF FG_Color;
		static std::vector<Command>Commands;
	public:
		static void setBackColor(COLORREF color);
		static void setForeColor(COLORREF color);
		static COLORREF getBackColor();
		static COLORREF getForeColor();
		static void AddCommand(Command c);
		static void AddCommand(int algorithm, int numberOfPoints, Point *points, COLORREF color);
		static void save();
		static void load();
};






#endif