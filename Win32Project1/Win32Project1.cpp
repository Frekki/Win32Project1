// Win32Project2223.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include <CommCtrl.h>

#define MAX_LOADSTRING 100

bool bDrawLine = false;
bool bDrawEllipse = false;

HWND button;
//HWND hWndTrack;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int lastx, lasty, x, y;		//GLOBAL VARIABLES used in drawing.
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND WINAPI CreateTrackbar(HWND, UINT, UINT, UINT, UINT);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	static TCHAR szAppName[] = TEXT("Paint");					//Winddow Class name
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Something goes wrong!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	hwnd = CreateWindow(szAppName,		 // window class name
		TEXT("Paint in Visual C++."),	 // window caption
		WS_OVERLAPPEDWINDOW,			// window style
		CW_USEDEFAULT,					// initial x position
		CW_USEDEFAULT,					// initial y position
		CW_USEDEFAULT,					// initial x size
		CW_USEDEFAULT,					// initial y size
		NULL,							// parent window handle
		NULL,							// window menu handle
		hInstance,						// program instance handle
		NULL);							// creation parameters
										//ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}
/*
HWND WINAPI CreateTrackbar(
	HWND hWnd,			//parrent window
	UINT iMin,			//min value
	UINT iMax,			//max value
	UINT iSelMin,		//min value of the choosen object
	UINT iSelMax		//max value of the choosen object
)
{
	hWndTrack = CreateWindowEx(
		0, 
		TRACKBAR_CLASS,											//class name
		TEXT("Color Set"),										//trackbar text
		WS_CHILD|WS_VISIBLE|TBS_AUTOTICKS|TBS_ENABLESELRANGE,	//styles
		10,10,													//x, y
		255,30,													//wight, height
		hWnd,													//parent
		NULL,													//menu
		hInst,													//instance
		NULL													
	);

	SendMessage(hWndTrack, TBM_SETRANGE, 
		(WPARAM)TRUE,								//redraw flag
		(LPARAM)MAKELONG(iMin, iMax));				//min&max position

	SendMessage(hWndTrack, TBM_SETPAGESIZE,
		0, (LPARAM)10);								//new page size

	SendMessage(hWndTrack, TBM_SETSEL,
		(WPARAM)FALSE,								//redraw flag
		(LPARAM)MAKELONG(iSelMin, iSelMax));

	SendMessage(hWndTrack, TBM_SETPOS, 
		(WPARAM)TRUE,								//redraw flag
		(LPARAM)iSelMin);

	SetFocus(hWndTrack);

	return hWndTrack;
}*/	//Slide bar class

void line(HDC _hdc, int x1, int y1, int x2, int y2)		//This function draws line by the given four coordinates.
{
	MoveToEx(_hdc, x1, y1, NULL);
	LineTo(_hdc, x2, y2);
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	//case WM_INITDIALOG:
	//{
	//	CreateTrackbar(hWnd, 0, 100, 10, 50);
	//	break;
	//}

	case WM_CREATE:
	{
		button = CreateWindow(TEXT("button"), TEXT("Set color"), WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 80, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_LINE:
			bDrawLine = !bDrawLine;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case IDM_ELLIPSE:
			bDrawEllipse = !bDrawEllipse;
			InvalidateRect(hWnd, 0, TRUE);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		/*switch (LOWORD(wParam))
		{
		case IDC_GET:
			char buf[10];
			int num = SendMessage(hWndTrack, TBM_GETPOS, 0, 0);
			itoa(num, buf, 10);
			MessageBox(NULL, buf, TEXT("Position"), MB_OK);
			break;

		case ID_CANCEL:
			EndDialog(hWnd, 0);
			return true;
			break;
		}*/
	}
	break;
	case WM_LBUTTONDOWN:						//If Left mouse button is pressed
		lastx = LOWORD(lParam);					//Store the x-coordiante in lastx
		lasty = HIWORD(lParam);					//Store the y-coordinate in lasty
		return 0;
	case WM_MOUSEMOVE:							//When mouse is moved on the client area (or form for VB users)
		hdc = GetDC(hWnd);						//hdc is handle to device context
		x = LOWORD(lParam);						//Store the current x 
		y = HIWORD(lParam);						//Store the current y
		if (wParam & MK_LBUTTON)				//If Left mouse button is down then draw
		{
			line(hdc, lastx, lasty, x, y);		//Draw the line frome the last pair of coordiates to current
			lastx = x;							//The current x becomes the lastx for next line to be drawn
			lasty = y;							//The current y becomes the lasty for next line to be drawn
		}
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		
		HPEN hPenOld;
		if (bDrawLine)
		{
			//Draw a red line
			HPEN hLinePen;
			COLORREF qLineColor;
			qLineColor = RGB(255, 0, 0);	//Change when got SetCloror Function
			hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
			hPenOld = (HPEN)SelectObject(hdc, hLinePen);

			MoveToEx(hdc, lastx, lasty, NULL);
			LineTo(hdc, x, y);

			SelectObject(hdc, hPenOld);
			DeleteObject(hLinePen);
		}

		if (bDrawEllipse)
		{
			//Draw a blue ellipse
			HPEN hEllipsePen;
			COLORREF qEllipseColor;
			qEllipseColor = RGB(0, 0, 255);	//Change when got SetColor Function
			hEllipsePen = CreatePen(PS_SOLID, 3, qEllipseColor);
			hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);

			Arc(hdc, 100, 100, lastx, lasty, 0, 0, 0, 0);

			SelectObject(hdc, hPenOld);
			DeleteObject(hEllipsePen);
		}

		GetClientRect(hWnd, &rect);
		//TextOut(hdc, 0, 0, "Programmer Paint", 53);
		EndPaint(hWnd, &ps);
		return 0;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
