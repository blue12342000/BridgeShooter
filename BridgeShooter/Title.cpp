#include "Title.h"
#include "Image.h"
#include "BridgeShooter.h"
#include "Animation.h"

HRESULT Title::Init()
{
    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpPressKey = ImageManager::GetSingleton()->FindImage("TITLE_PRESSKEY");
    lpTitle = ImageManager::GetSingleton()->FindImage("TITLE");
    lpMovingCat = new Animation();
    lpMovingCat->Change("MOVING_CAT", 24, true, false);
    catPos = {-50, 400 };

    return S_OK;
}

void Title::Release()
{
    
}

void Title::Update(float deltaTime)
{
    lpMovingCat->Update(deltaTime);
    catPos.x += deltaTime * 10;

    if (KeyManager::GetSingleton()->IsKeyDownOne(VK_SPACE))
    {
        SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::SELECT);
    }
}

void Title::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();
    if (lpTitle)
        lpTitle->Render(hBackDC);
    if (lpPressKey)
        lpPressKey->Render(hBackDC);
    if (lpMovingCat)
        lpMovingCat->Render(hBackDC, (int)catPos.x, (int)catPos.y);

    lpBackBuffer->Render(hdc);
}
