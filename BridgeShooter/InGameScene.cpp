#include "InGameScene.h"
#include "Image.h"
#include "SpaceShip.h"
#include "Planet_SSJ.h"
#include "Planet04.h"
#include "JinHwang.h"
#include "Planet_KMS.h"
#include "Item.h"

HRESULT InGameScene::Init()
{
    lpPlayer = new SpaceShip();
    lpPlayer->Init();
    lpPlayer->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT});

    lpPlanet04 = new Planet04();
    lpPlanet04->Init();
    lpPlanet04->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT/4 });

    lpPlanetSSJ = new Planet_SSJ();
    lpPlanetSSJ->Init();
    lpPlanetSSJ->SetPos({(float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpPlanetKMS = new Planet_KMS();
    lpPlanetKMS->Init();
    lpPlanetKMS->SetPos({ (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 });

    lpItem = new Item();
    lpItem->Init();
    lpItem->SetPos({ (float)WINSIZE_WIDTH *3/4, (float)WINSIZE_HEIGHT *7/8  });

    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    lpBackImage2 = ImageManager::GetSingleton()->FindImage("SPACE");
    frame = 0;
    elapsedTime = 0;
        
    backgroundMover = 0;

    lpJinHwang = new JinHwang();
    lpJinHwang->Init();
    lpJinHwang->SetPos({ (float)WINSIZE_WIDTH / 2 + 200, (float)WINSIZE_HEIGHT / 3 });

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

    if (lpPlanet04)
    {
        lpPlanet04->Release();
        delete lpPlanet04;
        lpPlanet04 = nullptr;
    }
    if (lpPlanetKMS)
    {
        lpPlanetKMS->Release();
        delete lpPlanetKMS;
        lpPlanetKMS = nullptr;
    }

    if (lpJinHwang)
    {
        lpJinHwang->Release();
        delete lpJinHwang;
        lpJinHwang = nullptr;
    }

    if (lpItem)
    {
        lpItem->Release();
        delete lpItem;
        lpItem = nullptr;
    }
}

void InGameScene::Update(float deltaTime)
{
    if (lpPlayer) lpPlayer->Update(deltaTime);
    if (lpPlanet04) lpPlanet04->Update(deltaTime);
    if (lpPlanetSSJ) lpPlanetSSJ->Update(deltaTime);
    if (lpJinHwang) lpJinHwang->Update(deltaTime);
    if (lpPlanetKMS) lpPlanetKMS->Update(deltaTime);
    
    if (lpItem) lpItem->Update(deltaTime);

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
    if (lpPlanet04) lpPlanet04->Render(hBackDC);
    if (lpJinHwang) lpJinHwang->Render(hBackDC);
    if (lpPlanetKMS) lpPlanetKMS->Render(hBackDC);

    if (lpItem) lpItem->Render(hBackDC);

    MissileManager::GetSingleton()->Render(hBackDC);

    lpBackBuffer->Render(hdc);
}
