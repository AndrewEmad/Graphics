#include <Windows.h>
#include <math.h>
#include <algorithm>
#include "Line.h"
#include "Circle.h"
#include "Curve.h"
#include "Filling.h"
#include "Colors.h"
#include "Clipping.h"
#include "Session.h"

void Init_WNDCLASS(WNDCLASS &wc, HINSTANCE h);
LRESULT WINAPI MyWindowProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp);
void Init_Menu(HMENU &hMenubar);
void CheckMenu(HMENU &hMenu, HMENU subMenus[], int cnt, int iD);

int APIENTRY WinMain(HINSTANCE h, HINSTANCE, LPSTR, int n)
{
	HWND hwnd;	
	WNDCLASS wc;
	HMENU hMenubar;
	MSG m;

	Init_WNDCLASS(wc, h);
	Init_Menu(hMenubar);
	RegisterClass(&wc);
	hwnd = CreateWindow(L"MainWindow", L"Drawing Package", WS_OVERLAPPED | WS_SYSMENU, 370, 92, 600, 600, NULL, hMenubar, h, NULL);
	ShowWindow(hwnd, n);
	
	while (GetMessage(&m, NULL, 0, 0)>0)
	{
		TranslateMessage(&m);
		DispatchMessage(&m);
	}
	return 0;
}

void Init_WNDCLASS(WNDCLASS &wc,HINSTANCE h){
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hInstance = h;
	wc.lpfnWndProc = MyWindowProc;
	wc.lpszClassName = L"MainWindow";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

}

void Init_Menu(HMENU &hMenubar){
	hMenubar = CreateMenu();
	HMENU file = CreateMenu();
	AppendMenuW(file, MF_STRING, 1, L"&New");
	AppendMenuW(file, MF_STRING, 2, L"&Open");
	AppendMenuW(file, MF_STRING, 3, L"&Save");
	
	HMENU clip = CreateMenu();
	AppendMenuW(clip, MF_STRING|MF_CHECKED, CLIPPING_NONE, L"&None");
	AppendMenuW(clip, MF_STRING, CLIPPING_RECTANGLE, L"&Rectangle");
	AppendMenuW(clip, MF_STRING, CLIPPING_CIRCLE, L"&Circle");
	AppendMenuW(file, MF_POPUP, (UINT_PTR)clip, L"&Set Drawing Area");

	AppendMenuW(file, MF_SEPARATOR, 0, NULL);
	AppendMenuW(file, MF_STRING, 4, L"&Quit");

	HMENU shapes = CreateMenu();
	HMENU line = CreateMenu();
	AppendMenuW(line, MF_STRING|MF_CHECKED, LINE_PARAMETRIC, L"&Parametric Method");
	AppendMenuW(line, MF_STRING, LINE_DIRECT, L"&Direct Method");
	AppendMenuW(line, MF_STRING, LINE_DDA, L"&DDA");
	AppendMenuW(line, MF_STRING, LINE_MIDPOINT, L"&MidPoint");
	AppendMenuW(shapes, MF_POPUP|MF_CHECKED, (UINT_PTR)line, L"&Line");

	HMENU circle = CreateMenu();
	AppendMenuW(circle, MF_STRING, CIRCLE_PARAMETRIC, L"&Parametric Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_DIRECT_CARTESIAN, L"&Direct Cartesian Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_DIRECT_POLAR, L"&Direct Polar Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_ITERATIVE_POLAR, L"&Iterative Polar Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_MIDPOINT, L"&MidPoint");
	AppendMenuW(shapes, MF_POPUP, (UINT_PTR)circle, L"&Circle");

	HMENU curve = CreateMenu();
	AppendMenuW(curve, MF_STRING, CURVE_FIRST_DEGREE, L"&First Degree Curve");
	AppendMenuW(curve, MF_STRING, CURVE_SECOND_DEGREE, L"&Second Degree Curve");
	AppendMenuW(curve, MF_STRING, CURVE_HERMIT, L"&Hermit Curve");
	AppendMenuW(curve, MF_STRING, CURVE_BEZIER, L"&Bezier Curve");
	AppendMenuW(curve, MF_STRING, CURVE_CARDINAL_SPLINE, L"&Cardinal Splines");
	AppendMenuW(shapes, MF_POPUP, (UINT_PTR)curve, L"&Curve");

	HMENU filled_shapes = CreateMenu();
	AppendMenuW(filled_shapes, MF_STRING, FILLED_SHAPES_CONVEX, L"&Convex");
	AppendMenuW(filled_shapes, MF_STRING, FILLED_SHAPES_POLYGON, L"&Polygon");
	AppendMenuW(shapes, MF_POPUP, (UINT_PTR)filled_shapes, L"&Filled Shapes");

	HMENU color = CreateMenu();
	HMENU bgcolor = CreateMenu();
	AppendMenuW(bgcolor, MF_STRING | MF_CHECKED, BG_WHITE, L"&White");
	AppendMenuW(bgcolor, MF_STRING, BG_RED, L"&Red");
	AppendMenuW(bgcolor, MF_STRING, BG_YELLOW, L"&Yellow");
	AppendMenuW(bgcolor, MF_STRING, BG_GREEN, L"&Green");
	AppendMenuW(bgcolor, MF_STRING, BG_BLUE, L"&Blue");
	AppendMenuW(bgcolor, MF_STRING, BG_BLACK, L"&Black");
	AppendMenuW(color, MF_POPUP, (UINT_PTR)bgcolor, L"&Background");

	HMENU fgcolor = CreateMenu();
	AppendMenuW(fgcolor, MF_STRING, FG_WHITE, L"&White");
	AppendMenuW(fgcolor, MF_STRING, FG_RED, L"&Red");
	AppendMenuW(fgcolor, MF_STRING, FG_YELLOW, L"&Yellow");
	AppendMenuW(fgcolor, MF_STRING, FG_GREEN, L"&Green");
	AppendMenuW(fgcolor, MF_STRING, FG_BLUE, L"&Blue");
	AppendMenuW(fgcolor, MF_STRING | MF_CHECKED, FG_BLACK, L"&Black");
	AppendMenuW(color, MF_POPUP, (UINT_PTR)fgcolor, L"&Foreground");

	HMENU fill = CreateMenu();
	AppendMenuW(fill, MF_STRING, FILLING_FLOODFILL_REC, L"&Recursive FloodFill");
	AppendMenuW(fill, MF_STRING, FILLING_FLOODFILL_NON_REC, L"&Non-Recursive FloodFill");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)file, L"&File");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)shapes, L"&Shapes");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)color, L"&Color");
}

void CheckMenu(HMENU &hMenu,HMENU subMenus[], int cnt,int p,int iD){
	if (p==0){
		for (int j = 0; j < cnt; ++j){
			char name[100];
			GetMenuString(hMenu, j, (LPWSTR)name, 100, MF_BYPOSITION);
			ModifyMenuW(hMenu, j, MF_BYPOSITION | MF_POPUP | MF_STRING, (UINT_PTR)(subMenus[j]), (LPWSTR)name);
			for (int i = LINE_PARAMETRIC; i <= FILLED_SHAPES_POLYGON; ++i){
				if (CheckMenuItem(subMenus[j], i, MF_STRING) != -1 && i == iD){
					CheckMenuItem(subMenus[j], i, MF_CHECKED);
					ModifyMenuW(hMenu, j, MF_BYPOSITION | MF_POPUP | MF_CHECKED, (UINT_PTR)(subMenus[j]), (LPWSTR)name);
				}
			}
		}
	}
	else if(p==1){
		for (int j = 0; j < cnt; ++j){
			for (int i = BG_WHITE; i <= BG_BLACK; ++i){
				if (CheckMenuItem(subMenus[j], i, MF_STRING) != -1 && i == iD){
					CheckMenuItem(subMenus[j], i, MF_CHECKED);
				}
			}
		}
	}
	else if (p == 2){
		for (int j = 0; j < cnt; ++j){
			for (int i = FG_WHITE; i <= FG_BLACK; ++i){
				if (CheckMenuItem(subMenus[j], i, MF_STRING) != -1 && i == iD){
					CheckMenuItem(subMenus[j], i, MF_CHECKED);
				}
			}
		}
	}
	else if (p == 3){
		for (int j = 0; j < cnt; ++j){
			for (int i = CLIPPING_RECTANGLE; i <= CLIPPING_NONE; ++i){
				if (CheckMenuItem(subMenus[j], i, MF_STRING) != -1 && i == iD){
					CheckMenuItem(subMenus[j], i, MF_CHECKED);
				}
			}
		}
	}
}

LRESULT WINAPI MyWindowProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	HMENU hMenu = GetMenu(hwnd);
	const int numberOfMenus = 4;
	HMENU FileMenu = GetSubMenu(hMenu, 0);
	HMENU ShapesMenu = GetSubMenu(hMenu, 1);
	HMENU subMenus[numberOfMenus];
	for (int i = 0; i < numberOfMenus;++i)
		subMenus[i] = GetSubMenu(ShapesMenu, i);
	
	HMENU ColorMenu = GetSubMenu(hMenu, 2);
	HMENU subColor[2];
	subColor[0] = GetSubMenu(ColorMenu, 0);
	subColor[1] = GetSubMenu(ColorMenu, 1);
	HMENU clipping = GetSubMenu(FileMenu, 3);
	static int Algorithm = LINE_PARAMETRIC;
	static int Clip = CLIPPING_NONE;
	static Point points[101];
	static int numberOfPoints = 0;

	switch (m)
	{

	case WM_LBUTTONDOWN:
		switch (Algorithm){
			case LINE_PARAMETRIC:
				points[numberOfPoints&1] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 2)
				{
					hdc = GetDC(hwnd);
					Line::DrawParametric(hdc, points[0].x, points[0].y, points[1].x, points[1].y, Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case LINE_DIRECT:
				points[numberOfPoints & 1] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 2)
				{
					hdc = GetDC(hwnd);
					Line::DrawDirect(hdc, points[0].x, points[0].y, points[1].x, points[1].y, Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case LINE_DDA:
				points[numberOfPoints & 1] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 2)
				{
					hdc = GetDC(hwnd);
					Line::DrawDDA(hdc, points[0].x, points[0].y, points[1].x, points[1].y, Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case LINE_MIDPOINT:
				points[numberOfPoints & 1] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 2)
				{
					hdc = GetDC(hwnd);
					Line::DrawMidPoint(hdc, points[0].x, points[0].y, points[1].x, points[1].y, Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CIRCLE_PARAMETRIC:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints == 2){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Circle::DrawParametricCircle(hdc, points[0].x, points[0].y, Circle::distance(points[0].x,points[0].y,points[1].x,points[1].y), Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CIRCLE_DIRECT_CARTESIAN:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints == 2){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Circle::DrawDirectCartesian(hdc, points[0].x, points[0].y, Circle::distance(points[0].x, points[0].y, points[1].x, points[1].y), Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CIRCLE_DIRECT_POLAR:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints == 2){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Circle::DrawDirectPolar(hdc, points[0].x, points[0].y, Circle::distance(points[0].x, points[0].y, points[1].x, points[1].y), Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CIRCLE_ITERATIVE_POLAR:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints == 2){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Circle::DrawIterativePolar(hdc, points[0].x, points[0].y, Circle::distance(points[0].x, points[0].y, points[1].x, points[1].y), Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CIRCLE_MIDPOINT:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints == 2){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Circle::DrawMidPoint(hdc, points[0].x, points[0].y, Circle::distance(points[0].x, points[0].y, points[1].x, points[1].y), Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CURVE_FIRST_DEGREE:
				points[numberOfPoints & 1] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 2){
					hdc = GetDC(hwnd);
					Curve::DrawFirstDegreeCurve(hdc, points[0], points[1], Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[2];
					memcpy(subPoints, points, 2 * sizeof(Point));
					Session::AddCommand(Algorithm, 2, subPoints, Session::getForeColor());
				}
				break;

			case CURVE_SECOND_DEGREE:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 3){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Curve::DrawSecondDegreeCurve(hdc, points[0], points[1],points[2], Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[3];
					memcpy(subPoints, points, 3 * sizeof(Point));
					Session::AddCommand(Algorithm, 3, subPoints, Session::getForeColor());
				}
				break;

			case CURVE_HERMIT:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 4){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Curve::DrawHermitCurve(hdc, points[0], points[1],points[2],points[3], Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[4];
					memcpy(subPoints, points, 4 * sizeof(Point));
					Session::AddCommand(Algorithm, 4, subPoints, Session::getForeColor());
				}

				break;

			case CURVE_BEZIER:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				if (numberOfPoints >= 4){
					numberOfPoints = 0;
					hdc = GetDC(hwnd);
					Curve::DrawBezierCurve(hdc, points[0], points[1], points[2], points[3], Session::getForeColor());
					ReleaseDC(hwnd, hdc);
					Point subPoints[4];
					memcpy(subPoints, points, 4 * sizeof(Point));
					Session::AddCommand(Algorithm, 4, subPoints, Session::getForeColor());
				}
				break;

			case CURVE_CARDINAL_SPLINE:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				break;

			case FILLED_SHAPES_CONVEX:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				break;

			case FILLED_SHAPES_POLYGON:
				points[numberOfPoints] = Point(LOWORD(lp), HIWORD(lp));
				numberOfPoints++;
				break;
		}
		break;
	


	case WM_RBUTTONDOWN:
		switch (Algorithm){
		case CURVE_CARDINAL_SPLINE:
			if (numberOfPoints > 2){
				hdc = GetDC(hwnd);
				Curve::DrawCardinalSpline(hdc, points,numberOfPoints, Session::getForeColor());
				ReleaseDC(hwnd, hdc);
				Session::AddCommand(Algorithm, numberOfPoints, points, Session::getForeColor());
				numberOfPoints = 0;
			}
			break;

		case FILLED_SHAPES_CONVEX:
			if (numberOfPoints > 2){
				hdc = GetDC(hwnd);
				Filling::convexFill(hdc, points, numberOfPoints, Session::getForeColor());
				ReleaseDC(hwnd, hdc);
				Session::AddCommand(Algorithm, numberOfPoints, points, Session::getForeColor());
				numberOfPoints = 0;
			}
			break;

		case FILLED_SHAPES_POLYGON:
			if (numberOfPoints > 2){
				hdc = GetDC(hwnd);
				Filling::polygonFill(hdc, points, numberOfPoints, Session::getForeColor());
				ReleaseDC(hwnd, hdc);
				Session::AddCommand(Algorithm, numberOfPoints, points, Session::getForeColor());
				numberOfPoints = 0;
			}
			break;
		}
		break;



	case WM_COMMAND:
		
		switch (LOWORD(wp)){
			case LINE_PARAMETRIC:
				CheckMenu(ShapesMenu, subMenus,numberOfMenus,0, LINE_PARAMETRIC);
				Algorithm = LINE_PARAMETRIC;
				numberOfPoints = 0;
				break;

			case LINE_DIRECT:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, LINE_DIRECT);
				Algorithm = LINE_DIRECT;
				numberOfPoints = 0;
				break;

			case LINE_DDA:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, LINE_DDA);
				Algorithm = LINE_DDA;
				numberOfPoints = 0;
				break;

			case LINE_MIDPOINT:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, LINE_MIDPOINT);
				Algorithm = LINE_MIDPOINT;
				numberOfPoints = 0;
				break;

			case CIRCLE_PARAMETRIC:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, CIRCLE_PARAMETRIC);
				Algorithm = CIRCLE_PARAMETRIC;
				numberOfPoints = 0;
				break;

			case CIRCLE_DIRECT_CARTESIAN:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, CIRCLE_DIRECT_CARTESIAN);
				Algorithm = CIRCLE_DIRECT_CARTESIAN;
				numberOfPoints = 0;
				break;

			case CIRCLE_DIRECT_POLAR:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, CIRCLE_DIRECT_POLAR);
				Algorithm = CIRCLE_DIRECT_POLAR;
				numberOfPoints = 0;
				break;

			case CIRCLE_ITERATIVE_POLAR:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, CIRCLE_ITERATIVE_POLAR);
				Algorithm = CIRCLE_ITERATIVE_POLAR;
				numberOfPoints = 0;
				break;

			case CIRCLE_MIDPOINT:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, CIRCLE_MIDPOINT);
				Algorithm = CIRCLE_MIDPOINT;
				numberOfPoints = 0;
				break;

			case CURVE_FIRST_DEGREE:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, CURVE_FIRST_DEGREE);
				Algorithm = CURVE_FIRST_DEGREE;
				numberOfPoints = 0;
				break;

			case CURVE_SECOND_DEGREE:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, CURVE_SECOND_DEGREE);
				Algorithm = CURVE_SECOND_DEGREE;
				numberOfPoints = 0;

				break;

			case CURVE_HERMIT:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, CURVE_HERMIT);
				Algorithm = CURVE_HERMIT;
				numberOfPoints = 0;
				break;

			case CURVE_BEZIER:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, CURVE_BEZIER);
				Algorithm = CURVE_BEZIER;
				numberOfPoints = 0;
				break;

			case CURVE_CARDINAL_SPLINE:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus,0, CURVE_CARDINAL_SPLINE);
				Algorithm = CURVE_CARDINAL_SPLINE;
				numberOfPoints = 0;
				break;

			case FILLED_SHAPES_CONVEX:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, FILLED_SHAPES_CONVEX);
				Algorithm = FILLED_SHAPES_CONVEX;
				numberOfPoints = 0;
				break;

			case FILLED_SHAPES_POLYGON:
				CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, FILLED_SHAPES_POLYGON);
				Algorithm = FILLED_SHAPES_POLYGON;
				numberOfPoints = 0;
				break;

			case BG_WHITE:
				CheckMenu(ColorMenu, &subColor[0], 1,1, BG_WHITE);
				SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(C_WHITE));
				Session::setBackColor(C_WHITE);
				InvalidateRect(hwnd, NULL, TRUE);
				break;

			case BG_RED:
				CheckMenu(ColorMenu, &subColor[0], 1,1, BG_RED);

				SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(C_RED));
				Session::setBackColor(C_RED);
				InvalidateRect(hwnd, NULL, TRUE);
				break;

			case BG_YELLOW:
				CheckMenu(ColorMenu, &subColor[0], 1,1, BG_YELLOW);

				SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(C_YELLOW));
				Session::setBackColor(C_YELLOW);
				InvalidateRect(hwnd, NULL, TRUE);
				break;

			case BG_GREEN:
				CheckMenu(ColorMenu, &subColor[0], 1,1, BG_GREEN);

				SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(C_GREEN));
				Session::setBackColor(C_GREEN);
				InvalidateRect(hwnd, NULL, TRUE);
				break;

			case BG_BLUE:
				CheckMenu(ColorMenu, &subColor[0], 1,1, BG_BLUE);

				SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(C_BLUE));
				Session::setBackColor(C_BLUE);
				InvalidateRect(hwnd, NULL, TRUE);
				break;

			case BG_BLACK:
				CheckMenu(ColorMenu, &subColor[0], 1,1, BG_BLACK);

				SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(C_BLACK));
				Session::setBackColor(C_BLACK);
				InvalidateRect(hwnd, NULL, TRUE);
				break;


			case FG_WHITE:
				CheckMenu(ColorMenu, &subColor[1], 1, 2, FG_WHITE);

				Session::setForeColor(C_WHITE);
				
				break;

			case FG_RED:
				CheckMenu(ColorMenu, &subColor[1], 1, 2, FG_RED);

				Session::setForeColor(C_RED);
				
				break;

			case FG_YELLOW:
				CheckMenu(ColorMenu, &subColor[1], 1, 2, FG_YELLOW);

				Session::setForeColor(C_YELLOW);
				
				break;

			case FG_GREEN:
				CheckMenu(ColorMenu, &subColor[1], 1, 2, FG_GREEN);
				Session::setForeColor(C_GREEN);
				
				break;

			case FG_BLUE:
				CheckMenu(ColorMenu, &subColor[1], 1, 2, FG_BLUE);
				Session::setForeColor(C_BLUE);
				
				break;

			case FG_BLACK:
				CheckMenu(ColorMenu, &subColor[1], 1, 2, FG_BLACK);
				Session::setForeColor(C_BLACK);
				break;

			case CLIPPING_NONE:
				CheckMenu(FileMenu, &clipping, 1, 3, CLIPPING_NONE);
				Clip = CLIPPING_NONE;
				numberOfPoints = 0;
				break;

			case CLIPPING_RECTANGLE:
				CheckMenu(FileMenu, &clipping, 1, 3, CLIPPING_RECTANGLE);
				Clip = CLIPPING_RECTANGLE;
				numberOfPoints = 0;
				break;

			case CLIPPING_CIRCLE:
				CheckMenu(FileMenu, &clipping, 1, 3, CLIPPING_CIRCLE);
				Clip = CLIPPING_CIRCLE;
				numberOfPoints = 0;
				break;

		}
		if (Clip == CLIPPING_CIRCLE || Clip == CLIPPING_RECTANGLE){
			CheckMenu(ShapesMenu, subMenus, numberOfMenus, 0, LINE_PARAMETRIC);
			for (int j = 1; j < numberOfMenus; ++j){
				EnableMenuItem(ShapesMenu, j, MF_BYPOSITION | MF_GRAYED);
			}
			for (int j = 1; j <= 3; ++j){
				EnableMenuItem(subMenus[0], j, MF_BYPOSITION | MF_GRAYED);
			}
		}
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, m, wp, lp);

	}
	return 0;
}

