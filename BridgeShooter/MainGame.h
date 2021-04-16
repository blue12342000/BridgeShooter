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
	void Render();	//HDC ������� �ߴµ� main.cpp 55��°�� ��ó g_mainGame.Render(); ���� ������

	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

