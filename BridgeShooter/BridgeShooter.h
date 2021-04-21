#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <float.h>
#include <random>

using namespace std;

#define WINPOS_STARTX 200
#define WINPOS_STARTY 200
#define WINSIZE_WIDTH 600
#define WINSIZE_HEIGHT 800

#define WINSIZE_LEFT -200
#define WINSIZE_TOP -200
#define WINSIZE_RIGHT 1000
#define WINSIZE_BOTTOM 1000

#define PI 3.141592f

#define U_IA_DEFAULT 0x00
#define U_IA_CENTER 0x01


#define U_MAX_PLAYER_HP 50
#define U_MAX_BOSS_HP 2000
#define U_MAX_ENEMY_HP 20

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern bool isDebugMode;

enum class UNIT_KIND
{
	PLAYER,
	ENEMY,
	BOSS,
	NONE
};

#include "KeyManager.h"
#include "ImageManager.h"
#include "MissileManager.h"
#include "EffectManager.h"
#include "MissileManager.h"
#include "SceneManager.h"
#include "DataManager.h"