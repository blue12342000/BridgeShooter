#pragma once

#include <Windows.h>
#include <vector>
#include <string>

#include <map>


using namespace std;

#define WINPOS_STARTX 200
#define WINPOS_STARTY 200
#define WINSIZE_WIDTH 800
#define WINSIZE_HEIGHT 800

#define PI 3.141592f

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern bool isDebugMode;