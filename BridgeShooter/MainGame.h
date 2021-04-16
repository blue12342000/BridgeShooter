#pragma once
#include "BridgeShooter.h"

class InGameScene;
class Timer;
class MainGame
{
private:
	HDC hdc;
	Timer* lpTimer;
	InGameScene* lpScene;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

