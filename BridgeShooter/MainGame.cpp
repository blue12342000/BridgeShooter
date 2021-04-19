#include "MainGame.h"
#include "BridgeShooter.h"
#include "Timer.h"
#include "InGameScene.h"
#include "Title.h"

HRESULT MainGame::Init()
{
    srand(time(NULL));

    KeyManager::GetSingleton()->Init();
    ImageManager::GetSingleton()->Init();
    MissileManager::GetSingleton()->Init();
    EffectManager::GetSingleton()->Init();
    SceneManager::GetSingleton()->Init();
    DataManager::GetSingleton()->Init();

    hdc = GetDC(g_hWnd);
    
    lpTimer = new Timer();
    lpTimer->Init();
  
    return S_OK;
}

void MainGame::Release()
{

    if (lpTimer)
    {
        delete lpTimer;
        lpTimer = nullptr;
    }
 
    MissileManager::GetSingleton()->Release();
    MissileManager::GetSingleton()->ReleaseSingleton();
    KeyManager::GetSingleton()->ReleaseSingleton();
    ImageManager::GetSingleton()->Release();
    ImageManager::GetSingleton()->ReleaseSingleton();
    SceneManager::GetSingleton()->Release();
    SceneManager::GetSingleton()->ReleaseSingleton();
    EffectManager::GetSingleton()->ReleaseSingleton();
    DataManager::GetSingleton()->ReleaseSingleton();

    ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
    if (KeyManager::GetSingleton()->IsKeyDownOne('P'))
    {
        isDebugMode = !isDebugMode;
    }

    lpTimer->Tick();

    SceneManager::GetSingleton()->Update(lpTimer->GetDeltaTime());
    //datamanager
}

void MainGame::Render()
{
    lpTimer->Render(hdc);

    SceneManager::GetSingleton()->Render(hdc);

    
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
