#include <Windows.h>
#include <math.h>
#include <algorithm>
#include "Line.h"
#include "Circle.h"
#include "Curve.h"

#define BG_WHITE 100
#define BG_RED 101
#define BG_YELLOW 102
#define BG_GREEN 103
#define BG_BLUE 104
#define BG_BLACK 105

#define FG_WHITE 106
#define FG_RED 107
#define FG_YELLOW 108
#define FG_GREEN 109
#define FG_BLUE 110
#define FG_BLACK 111


void Init_WNDCLASS(WNDCLASS &wc, HINSTANCE h);
LRESULT WINAPI MyWindowProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp);
void Init_Menu(HMENU &hMenubar);

int APIENTRY WinMain(HINSTANCE h, HINSTANCE, LPSTR, int n)
{
	HWND hwnd,hWndButton;	
	WNDCLASS wc;
	HMENU hMenubar;
	MSG m;

	Init_WNDCLASS(wc, h);
	Init_Menu(hMenubar);
	RegisterClass(&wc);
	hwnd = CreateWindow(L"MainWindow", L"Drawing Package", WS_OVERLAPPEDWINDOW, 80, 90, 600, 600, NULL, hMenubar,h, NULL);
	//hWndButton = CreateWindow(L"BUTTON",L"OK",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,0,0,100,24,hwnd,NULL,(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
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
	AppendMenuW(file, MF_SEPARATOR, 0, NULL);
	AppendMenuW(file, MF_STRING, 4, L"&Quit");

	HMENU algorithms = CreateMenu();
	HMENU line = CreateMenu();
	AppendMenuW(line, MF_STRING, LINE_PARAMETRIC, L"&Parametric Method");
	AppendMenuW(line, MF_STRING, LINE_Direct, L"&Direct Method");
	AppendMenuW(line, MF_STRING, LINE_DDA, L"&DDA");
	AppendMenuW(line, MF_STRING, LINE_MIDPOINT, L"&MidPoint");
	AppendMenuW(algorithms, MF_POPUP, (UINT_PTR)line, L"&Line");

	HMENU circle = CreateMenu();
	AppendMenuW(circle, MF_STRING, CIRCLE_DIRECT_CARTESIAN, L"&Direct Cartesian Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_DIRECT_POLAR, L"&Direct Polar Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_ITERATIVE_POLAR, L"&Iterative Polar Method");
	AppendMenuW(circle, MF_STRING, CIRCLE_MIDPOINT, L"&MidPoint");
	AppendMenuW(algorithms, MF_POPUP, (UINT_PTR)circle, L"&Circle");

	HMENU curve = CreateMenu();
	AppendMenuW(curve, MF_STRING, CURVE_HERMIT, L"&Hermit Curve");
	AppendMenuW(curve, MF_STRING, CURVE_CADINAL_SPLINES, L"&Cardinal Splines");
	AppendMenuW(algorithms, MF_POPUP, (UINT_PTR)curve, L"&Curve");

	HMENU color = CreateMenu();
	HMENU bgcolor = CreateMenu();
	AppendMenuW(bgcolor, MF_STRING, BG_WHITE, L"&White");
	AppendMenuW(bgcolor, MF_STRING, BG_RED, L"&Red");
	AppendMenuW(bgcolor, MF_STRING,BG_YELLOW, L"&Yellow");
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
	AppendMenuW(fgcolor, MF_STRING, FG_BLACK, L"&Black");
	AppendMenuW(color, MF_POPUP, (UINT_PTR)fgcolor, L"&Foreground");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)file, L"&File");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)algorithms, L"&Algorithms");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)color, L"&Color");
}



LRESULT WINAPI MyWindowProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
	HDC hdc;

	switch (m)
	{

	case WM_COMMAND:
		switch(LOWORD(wp))
			case 1:
				MessageBox(hwnd,L"HELLO!",L"Caption",NULL);
				break;
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, m, wp, lp);

	}
	return 0;
}

