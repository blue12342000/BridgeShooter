#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet_SSJ.h"
#include "Planet.h"
#include"Planet_KMS.h"

HRESULT InGameScene::Init()
{
    lpPlayer = new SpaceShip();
    lpPlayer->Init();
    lpPlayer->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT});

    //테스트용 플래닛 추가
    lpPlanet = new Planet();
    lpPlanet->Init();
    lpPlanet->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT/6 });

    lpPlanetSSJ = new Planet_SSJ();
    lpPlanetSSJ->Init();
    lpPlanetSSJ->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpPlanetKMS = new Planet_KMS();
    lpPlanetKMS->Init();
    lpPlanetKMS->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });


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


    if (lpPlanetSSJ)
    {
        lpPlanetSSJ->Release();
        delete lpPlanetSSJ;
        lpPlanetSSJ = nullptr;
    }

    if (lpPlanet)
    {
        lpPlanet->Release();
        delete lpPlanet;
        lpPlanet = nullptr;
    }
    if (lpPlanetKMS)
    {
        lpPlanetKMS->Release();
        delete lpPlanetKMS;
        lpPlanetKMS = nullptr;
    }


}

void InGameScene::Update(float deltaTime)
{
    if (lpPlayer) lpPlayer->Update(deltaTime);
    if (lpPlanet) lpPlanet->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);

    if (lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    if (lpPlanetKMS) lpPlanetKMS->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);
}

void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage) lpBackImage->Render(hBackDC);
    if (lpPlayer) lpPlayer->Render(hBackDC);

    if (lpPlanetSSJ) lpPlanetSSJ->Render(hBackDC);

    if (lpPlanet) lpPlanet->Render(hBackDC);
    if (lpPlanetKMS) lpPlanetKMS->Render(hBackDC);

    MissileManager::GetSingleton()->Render(hBackDC);

    lpBackBuffer->Render(hdc);
}
