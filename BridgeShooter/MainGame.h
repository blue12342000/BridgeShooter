#pragma once
#include "BridgeShooter.h"

class InGameScene;
class Timer;
class MainGame
{
private:
	HDC hdc;
	Timer* lptimer;
	InGameScene* lpScene;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();	//HDC 넣을라고 했는데 main.cpp 55번째줄 근처 g_mainGame.Render(); 쪽이 에러남

	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

