#include "GameClear.h"
#include "Planet_SSJ.h"
#include "Image.h"
#include "PlayerController.h"

HRESULT GameClear::Init()
{
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
     
    lpPlayerController = new PlayerController();
    lpPlayerController->Init();
    lpPlayerController->SetUnit(new Planet_SSJ());
    lpPlayerController->GetUnit()->pos = { WINSIZE_WIDTH / 2, WINSIZE_HEIGHT };
    lpPlayerController->GetUnit()->SetFactoryLine(3);

    return S_OK;
}

void GameClear::Release()
{   
    if (lpPlayerController)
    {
        lpPlayerController->Release();
        delete lpPlayerController;
        lpPlayerController = nullptr;
    }
    
}

void GameClear::Update(float deltaTime)
{
    MissileManager::GetSingleton()->Update(deltaTime);
    lpPlayerController->Update(deltaTime);
}

void GameClear::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

   
    if (lpBackImage) lpBackImage->Render(hBackDC);
    if (lpPlayerController)    lpPlayerController->Render(hBackDC);
    MissileManager::GetSingleton()->Render(hBackDC);
    
    lpBackBuffer->Render(hdc);
}
