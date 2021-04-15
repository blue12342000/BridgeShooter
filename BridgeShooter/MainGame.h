#pragma once
#include "BridgeShooter.h"

class MainGame
{
private:
	HDC hdc;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

