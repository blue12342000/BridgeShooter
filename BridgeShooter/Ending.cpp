#include "Ending.h"
#include "BridgeShooter.h"
#include "Image.h"
#include "Animation.h"

HRESULT Ending::Init()
{
    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
    lpRetry = ImageManager::GetSingleton()->FindImage("ENDING");
    lpGhoust = new Animation();
    lpGhoust->Change("Ghoust", 6, true);
    backgroundMover = 0;
    return S_OK;
}

void Ending::Release()
{
    delete lpGhoust;
}

void Ending::Update(float deltaTime)
{
    if (KeyManager::GetSingleton()->IsKeyDownOne(VK_ESCAPE))
    {
        SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::TITLE);
    }
    lpGhoust->Update(deltaTime);

    backgroundMover += 300 * deltaTime;
    if (backgroundMover >= 800) backgroundMover = 0;
}

void Ending::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();
    if (lpBackImage)
    {
        lpBackImage->Render(hBackDC, 0, backgroundMover);
        lpBackImage->Render(hBackDC, 0, -800 + backgroundMover);
    }
    if (lpRetry) 
        lpRetry->Render(hBackDC);
    if (lpGhoust)
        lpGhoust->Render(hBackDC, WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 2 - 100);

    lpBackBuffer->Render(hdc);
}
