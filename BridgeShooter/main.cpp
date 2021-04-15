#include "BridgeShooter.h"

HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("Bridge Shooter");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void SetWindowSize(HWND hWnd, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITENESS);
	wndClass.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	wndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, WINSIZE_WIDTH, WINSIZE_HEIGHT, NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nShowCmd);

	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{

		}
	}
}

void SetWindowSize(HWND hWnd, int width, int height)
{
	RECT rect;
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	SetRect(&rect, 0, 0, WINSIZE_WIDTH, WINSIZE_HEIGHT);
	AdjustWindowRect(&rect, dwStyle, GetMenu(hWnd) != NULL);
	

	SetWindowPos(hWnd, NULL, WINPOS_STARTX, WINPOS_STARTY, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}
