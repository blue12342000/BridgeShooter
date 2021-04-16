#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet_SSJ.h"

HRESULT InGameScene::Init()
{
    lpPlayer = new SpaceShip();
    lpPlayer->Init();
    lpPlayer->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT});

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    frame = 0;
    elapsedTime = 0;

    lpPlanetSSJ = new Planet_SSJ();
    lpPlanetSSJ->Init();
    lpPlanetSSJ->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

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

    if (lpPlanetSSJ)
    {
        lpPlanetSSJ->Release();
        delete lpPlanetSSJ;
        lpPlanetSSJ = nullptr;
    }
}

void InGameScene::Update(float deltaTime)
{
    if (lpPlayer) lpPlayer->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);

    if (lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);
}

void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage) lpBackImage->Render(hBackDC);
    if (lpPlayer) lpPlayer->Render(hBackDC);
    if (lpPlanetSSJ) lpPlanetSSJ->Render(hBackDC);
    MissileManager::GetSingleton()->Render(hBackDC);

    lpBackBuffer->Render(hdc);
}
