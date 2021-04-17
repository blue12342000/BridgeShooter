#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet_SSJ.h"
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

    lpPlanetSSJ = new Planet_SSJ();
    lpPlanetSSJ->Init();
    lpPlanetSSJ->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    lpBackImage2 = ImageManager::GetSingleton()->FindImage("SPACE");
    frame = 0;
    elapsedTime = 0;
        
    backgroundMover = 0;

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

}

void InGameScene::Update(float deltaTime)
{
    if (lpPlayer) lpPlayer->Update(deltaTime);
    if (lpPlanet) lpPlanet->Update(deltaTime);
    if (lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);

    MissileManager::GetSingleton()->Update(deltaTime);
    MissileManager::GetSingleton()->Update(deltaTime);

    backgroundMover += 0.1f;
    if (backgroundMover >= 800) backgroundMover = 0;
}

void InGameScene::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    if (lpBackImage) lpBackImage->Render(hBackDC, 0, backgroundMover);
    if (lpBackImage2) lpBackImage2->Render(hBackDC, 0, -800+backgroundMover);

    if (lpPlayer) lpPlayer->Render(hBackDC);

    if (lpPlanetSSJ) lpPlanetSSJ->Render(hBackDC);

    if (lpPlanet) lpPlanet->Render(hBackDC);
    
    MissileManager::GetSingleton()->Render(hBackDC);

    lpBackBuffer->Render(hdc);
}
