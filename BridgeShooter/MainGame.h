#pragma once
#include "BridgeShooter.h"

class Timer;
class MainGame
{
private:
	HDC hdc;
	Timer* lptimer;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

