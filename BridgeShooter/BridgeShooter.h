#pragma once

#include <iostream>
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

#define U_IA_DEFAULT 0x00
#define U_IA_CENTER 0x01

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern bool isDebugMode;

enum class UNIT_KIND
{
	PLAYER,
	ENEMY,
	NONE
};

#include "KeyManager.h"
#include "ImageManager.h"
#include "MissileManager.h"