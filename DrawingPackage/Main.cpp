#include <Windows.h>
#include <math.h>
#include <algorithm>

void Init_WNDCLASS(WNDCLASS &wc, HINSTANCE h);
LRESULT WINAPI MyWindowProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp);
void Init_Menu(HMENU &hMenubar);

int APIENTRY WinMain(HINSTANCE h, HINSTANCE, LPSTR, int n)
{
	HWND hwnd,hWndButton;	
	WNDCLASS wc;
	HMENU hMenubar;
	Init_WNDCLASS(wc, h);
	Init_Menu(hMenubar);
	RegisterClass(&wc);
	hwnd = CreateWindow(L"MainWindow", L"Drawing Package", WS_OVERLAPPEDWINDOW, 80, 90, 600, 600, NULL, hMenubar,h, NULL);
	//hWndButton = CreateWindow(L"BUTTON",L"OK",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,0,0,100,24,hwnd,NULL,h,NULL);
	ShowWindow(hwnd, n);
	MSG m;
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
	wc.lpszMenuName = L"hm";
	wc.style = CS_VREDRAW | CS_HREDRAW;

}

void Init_Menu(HMENU &hMenubar){
	hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();
	AppendMenuW(hMenu, MF_STRING, 1, L"&New");
	AppendMenuW(hMenu, MF_STRING, 2, L"&Open");
	AppendMenuW(hMenu, MF_STRING, 3, L"&Save");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, 3, L"&Quit");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
}



LRESULT WINAPI MyWindowProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
	HDC hdc;

	switch (m)
	{

	case WM_LBUTTONUP:

		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, m, wp, lp);

	}
	return 0;
}

