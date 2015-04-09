#define DEBUG

#include "Init.h" 
#include "CDirect2D.h"
#define KEYDOWN(vk_code)\
						((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
//---------------------------------------------------
//GLOBALS
ID2D1HwndRenderTarget *pRenderTarget;
//---------------------------------------------------

const TCHAR *	MAIN_WINDOW_CLASS_NAME = _T("MainWindow");				//Window Class Name
const TCHAR *	MAIN_WINDOW_TITLE = _T("Saboteur");						//Window Title
const int		WINDOW_WIDTH = 640;
const int		WINDOW_HEIGHT = 480;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#ifndef DEBUG
#define WinMain_ WinMain
#else

HINSTANCE hInstance, hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
  
int WINAPI WinMain_(HINSTANCE, HINSTANCE, LPSTR, int);
int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	WinMain_(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}

#endif

//-----------------------------------------------------------------
//-----------------------------VARs--------------------------------
CDirect2D * d2d = CDirect2D::getInstance();
//-----------------------------------------------------------------

int WINAPI WinMain_(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = MAIN_WINDOW_CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), NULL, NULL);
		return 1;
	}

	HWND hWnd = CreateWindow(
		MAIN_WINDOW_CLASS_NAME,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindow failed!"), NULL, NULL);
		return 1;
	}

	CoInitialize(NULL);
	d2d = CDirect2D::getInstance();
	d2d->setHWND(hWnd);
	d2d->init();
	d2d->createRenderObject("test", L"test.png");
	d2d->createRenderObject("star1", L"Great.png");
	d2d->getRenderObject("star1")->setXY(70, 60);
	//d2d->createRenderObject("star2", L"Great.png");
	//d2d->getRenderObject("test")->setXY(200, 200);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;
	int x, y;
	x = y = 0;
	int speed = 3;
	while (true)
	{
		DWORD start_time = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (KEYDOWN(VK_RIGHT))
			x+=speed;
		if (KEYDOWN(VK_LEFT))
			x -= speed;
		if (KEYDOWN(VK_UP))
			y -= speed;
		if (KEYDOWN(VK_DOWN))
			y += speed;
		d2d->getRenderObject("star1")->setXY(x, y);
		d2d->draw();
		while ((GetTickCount() - start_time) < 33);
	} //main loop


	//
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

	CoUninitialize();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//d2d->draw();
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}