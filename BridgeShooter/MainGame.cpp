#include "MainGame.h"

HRESULT MainGame::Init()
{
    TimerManager::GetSingleton()->Init();
    HDC hdc = GetDC(g_hWnd);

    return S_OK;
}

void MainGame::Release()
{
    TimerManager::GetSingleton()->Release();
    TimerManager::GetSingleton()->ReleaseSingleton();
    ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
}

void MainGame::Render()
{
    float ct = TimerManager::GetSingleton()->GetCurrTime();
    float dt = TimerManager::GetSingleton()->GetDeltaTime();
    int i = 0;
}

LRESULT MainGame::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
