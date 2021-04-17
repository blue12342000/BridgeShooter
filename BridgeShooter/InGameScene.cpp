#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet.h"

HRESULT InGameScene::Init()
{
    lpPlayer = new SpaceShip();
    lpPlayer->Init();
    lpPlayer->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT});

    //테스트용 플래닛 추가
    lpPlanet = new Planet();
    lpPlanet->Init();
    lpPlanet->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT/6 });

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    frame = 0;
    elapsedTime = 0;

    return S_OK;
}

void InGameScene::Release()
{
    if (lpPlayer)
    {
        lpPlayer->Release();
        delete lpPlayer;
        lpPlayer = nullptr;
    }
    if (lpPlanet)
    {
        lpPlanet->Release();
        delete lpPlanet;
        lpPlanet = nullptr;
    }

}

void InGameScene::Update(float deltaTime)
{
    if (lpPlayer) lpPlayer->Update(deltaTime);
    if (lpPlanet) lpPlanet->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);
}

void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage) lpBackImage->Render(hBackDC);
    if (lpPlayer) lpPlayer->Render(hBackDC);
    if (lpPlanet) lpPlanet->Render(hBackDC);
    MissileManager::GetSingleton()->Render(hBackDC);

    lpBackBuffer->Render(hdc);
}
