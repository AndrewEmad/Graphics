#ifndef FILLING_H
#define FILLING_H
#include<Windows.h>
#include<Windows.h>
#include<stack>
#include<vector>
#include<algorithm>


#define FILLED_SHAPES_CONVEX 19
#define FILLED_SHAPES_POLYGON 20
#define FILLING_FLOODFILL_REC 21
#define FILLING_FLOODFILL_NON_REC 22

struct Edge{
	int xmin;
	int xmax;
	Edge(){}
	Edge(int xi, int xm){
		xmin = xi;
		xmax = xm;
	}
};

struct EdgeRec {
	double x;
	double minv;
	int ymax;
	EdgeRec(){}
	EdgeRec(double x1, double m1, int y1){
		x = x1;
		minv = m1;
		ymax = y1;
	}
	bool operator<(EdgeRec r)
	{
		return x<r.x;
	}
};

class Filling{
	private:
		static EdgeRec getRecord(POINT &v1, POINT &v2);
		static void initEdgeRecTable(POINT *polygon, int n, std::vector<EdgeRec> table[]);
		static void initEdgeTable(Edge tbl[]);
		static void constructEdges(POINT v1, POINT v2, Edge tbl[]);

	public:
		static void convexFill(HDC hdc, POINT *polygon, int n, COLORREF color);
		static void polygonFill(HDC hdc, POINT *polygon, int n, COLORREF color);
		static void FloodFillNonRec(HDC hdc, int x, int y, COLORREF bc, COLORREF fc);
		static void FloodFillRec(HDC hdc, int x, int y, COLORREF bc, COLORREF fc);

};





#endif