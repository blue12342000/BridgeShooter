#include "MainGame.h"
#include "Timer.h"
HRESULT MainGame::Init()
{
    HDC hdc = GetDC(g_hWnd);

    KeyManager::GetSingleton()->Init();
    lpTimer = new Timer();
    lpTimer->Init();
  

    return S_OK;
}

void MainGame::Release()
{
    KeyManager::GetSingleton()->ReleaseSingleton();

    if (lpTimer)
    {
        delete lpTimer;
        lpTimer = nullptr;
    }
  
    ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
}

void MainGame::Render()
{
}

LRESULT MainGame::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
