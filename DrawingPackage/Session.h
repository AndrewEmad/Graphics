#ifndef SESSION_H
#define SESSION_H
#include<vector>


struct Point{
	int x;
	int y;

	Point(){}
	Point(int x1,int y1){
		x = x1;
		y = y1;
	}
};

struct Command{
	int Algorithm;
	int Color;
	int numberOfPoints;
	Point *points;
	
	Command(int alg, int clr, int nop ,Point*p){
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
		static int BG_Color;
		static int FG_Color;
		static std::vector<Command>Commands;
	public:
		static void setBackColor(int color);
		static void setForeColor(int color);
		static void AddCommand(Command c);
		static void AddCommand(int algorithm, int numberOfPoints, Point *points, int color);
		static void save();
		static void load();
};






#endif