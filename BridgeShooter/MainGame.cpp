#include "MainGame.h"
#include "Timer.h"
#include "InGameScene.h"

HRESULT MainGame::Init()
{
    KeyManager::GetSingleton()->Init();
    ImageManager::GetSingleton()->Init();

    hdc = GetDC(g_hWnd);
    
    lpTimer = new Timer();
    lpTimer->Init();
  
    lpScene = new InGameScene();
    lpScene->Init();

    return S_OK;
}

void MainGame::Release()
{

    if (lpTimer)
    {
        delete lpTimer;
        lpTimer = nullptr;
    }

    if (lpScene)
    {
        lpScene->Release();
        delete lpScene;
        lpScene = nullptr;
    }
  
    KeyManager::GetSingleton()->ReleaseSingleton();
    ImageManager::GetSingleton()->Release();
    ImageManager::GetSingleton()->ReleaseSingleton();

    ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
    if (lpScene) lpScene->Update(lpTimer->GetDeltaTime());
}

void MainGame::Render()
{
    if (lpScene) lpScene->Render(hdc);
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
