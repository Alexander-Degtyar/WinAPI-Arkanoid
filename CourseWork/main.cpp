// CourseWork.cpp : Defines the entry point for the application.
//


#include "CourseWork.h"
#include <time.h>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"Primitive Arkanoid";                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING] = L"Alexander Degtyar";            // the main window class name
RECT rc;
HWND hWnd;
HDC hdc;
Pressed pressed;
HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(100, 200, 0));
HPEN hBackgroundPen = CreatePen(BS_SOLID, 1, RGB(100, 200, 0));

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Thread(LPVOID lpParam);

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
    LoadStringW(hInstance, IDC_COURSEWORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEWORK));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }



    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = hBackgroundBrush;
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_COURSEWORK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   hWnd = CreateWindowW(szWindowClass, szTitle, (WS_SYSMENU | WS_MINIMIZEBOX),
      CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, nullptr, nullptr, hInstance, nullptr); //

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
	HANDLE hThread;
	

    switch (message)
    {
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
	{
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &rc);
		hThread = CreateThread(NULL, 0, Thread, 0, 0, 0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam) 
		{
		case VK_LEFT:
			pressed.leftArrow = true;
			break;

		case VK_RIGHT:
			pressed.rightArrow = true;
			break;
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		case 0x57: // W
			pressed.W = true;
			break;
		case 0x53: // S
			pressed.S = true;
			break;
		case 0x41: // A
			pressed.A = true;
			break;
		case 0x44: // D
			pressed.D = true;
			break;
		case 0x52: // R
			pressed.R = true;
			break;
		default:
			break;
		}
		break;
	}
	case WM_KEYUP:
	{
		switch (wParam) 
		{
		case VK_LEFT:
			pressed.leftArrow = false;
			break;
		case VK_RIGHT:
			pressed.rightArrow = false;
			break;
		case 0x57: // W
			pressed.W = false;
			break;
		case 0x53: // S
			pressed.S = false;
			break;
		case 0x41: // A
			pressed.A = false;
			break;
		case 0x44: // D
			pressed.D = false;
			break;
		case 0x52: // R
			pressed.R = false;
			break;
		default:
			break;
		}
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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

DWORD WINAPI Thread(LPVOID lpParam)
{
	CONST INT timeout = 1000 / 40;

	// configure ball
	Ball ball( ( rc.right / 2 ), ( rc.bottom / 2 ), 10, RGB(229, 43, 80));

	// configure pad
	Pad pad( ( rc.right / 2 ), ( rc.bottom - 20 ), 200, RGB(0, 127, 255));

	//HDC hdc = GetDC(hWnd);
	HBRUSH oldBr;
	HPEN oldPen;

	// game objects movement
	while (true)
	{
		// Instructions
		WCHAR ins1[] = L"ESC : Exit | R : Restart";
		WCHAR ins2[] = L"W : + | S : - ball speed on X axis";
		WCHAR ins3[] = L"D : + | A : - ball speed on Y axis";
		TextOut(hdc, 10, 10, (LPCWSTR)ins1, 25);
		TextOut(hdc, 10, 30, (LPCWSTR)ins2, 35);
		TextOut(hdc, 10, 50, (LPCWSTR)ins3, 35);
		/***********************************************************************************************/
		// Ball movement
		// Setting speed depending on the pressed keys
		if (pressed.W)
		{
			if (ball.getSpeedY() >= 0)
				ball.changeSpeedY(1);
			else 
				ball.changeSpeedY(-1);
		}
		else if (pressed.S)
		{
			if (ball.getSpeedY() >= 0)
				ball.changeSpeedY(-1);
			else
				ball.changeSpeedY(1);
		}
		else if (pressed.D)
		{
			if (ball.getSpeedX() >= 0)
				ball.changeSpeedX(1);
			else
				ball.changeSpeedX(-1);
		}
		else if (pressed.A)
		{
			if (ball.getSpeedX() >= 0)
				ball.changeSpeedX(-1);
			else
				ball.changeSpeedX(1);
		}

		oldBr = (HBRUSH)SelectObject(hdc, hBackgroundBrush);
		oldPen = (HPEN)SelectObject(hdc, hBackgroundPen);
		Ellipse(hdc,
			ball.coord(Ball::Side::LEFT), ball.coord(Ball::Side::TOP),
			ball.coord(Ball::Side::RIGHT), ball.coord(Ball::Side::BOTTOM));
		
		// Restart game
		if (pressed.R)
		{
			ball.setX(rc.right / 2);
			ball.setY(rc.bottom / 2);
			ball.setSpeedX(0);
			ball.setSpeedY(0);
		}

		ball.move();

		(HBRUSH)SelectObject(hdc, ball.getBrush());
		(HPEN)SelectObject(hdc, ball.getPen());
		Ellipse(hdc,
			ball.coord(Ball::Side::LEFT), ball.coord(Ball::Side::TOP),
			ball.coord(Ball::Side::RIGHT), ball.coord(Ball::Side::BOTTOM));
		
		// Bouncing the ball off the walls
		if (ball.coord(Ball::Side::LEFT) <= rc.left || ball.coord(Ball::Side::RIGHT) >= rc.right)
		{
			ball.bounceX();
		}
		else if (ball.coord(Ball::Side::TOP) <= rc.top)
		{
			ball.bounceY();
		}
		/***********************************************************************************************/
		// Bouncing the ball off the pad
		if ((pad.coord(Pad::Side::LEFT) <= ball.coord(Ball::Side::X) && ball.coord(Ball::Side::X) <= pad.coord(Pad::Side::RIGHT)) && (ball.coord(Ball::Side::BOTTOM)>=pad.coord(Pad::Side::TOP)))
		{
			ball.bounceY();
		}
		/***********************************************************************************************/
		// Pad movement
		
		// Setting speed depending on the pressed keys
		if (pressed.leftArrow && pressed.rightArrow)
			pad.setSpeed(0);
		else if (pressed.leftArrow)
			pad.setSpeed(-10);
		else if (pressed.rightArrow)
			pad.setSpeed(10);
		else
			pad.setSpeed(0);

		(HBRUSH)SelectObject(hdc, hBackgroundBrush);
		(HPEN)SelectObject(hdc, hBackgroundPen);
		
		Rectangle(hdc,
			pad.coord(Pad::Side::LEFT), pad.coord(Pad::Side::TOP),
			pad.coord(Pad::Side::RIGHT), pad.coord(Pad::Side::BOTTOM));

		pad.move();

		(HBRUSH)SelectObject(hdc, pad.getBrush());
		(HPEN)SelectObject(hdc, pad.getPen());
		
		Rectangle(hdc,
			pad.coord(Pad::Side::LEFT), pad.coord(Pad::Side::TOP),
			pad.coord(Pad::Side::RIGHT), pad.coord(Pad::Side::BOTTOM));

		// Bouncing the pad off the walls
		int deltaX = rc.left - pad.coord(Pad::Side::LEFT);
		if ( deltaX > 0 )
		{
			pad.changeCoords(deltaX, 0);
		}
		deltaX = rc.right - pad.coord(Pad::Side::RIGHT);
		if (deltaX < 0)
		{
			pad.changeCoords(deltaX, 0);
		}
		/***********************************************************************************************/
		Sleep(timeout);
	}
	// destroy draw objects
	(HBRUSH)SelectObject(hdc, oldBr);
	(HPEN)SelectObject(hdc, oldPen);
	ReleaseDC(hWnd, hdc);
	return 0;
}