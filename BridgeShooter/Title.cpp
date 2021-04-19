#include "Title.h"
#include "Image.h"
#include "BridgeShooter.h"

HRESULT Title::Init()
{
    lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
    lpPressKey = ImageManager::GetSingleton()->FindImage("TITLE_PRESSKEY");
    lpTitle = ImageManager::GetSingleton()->FindImage("TITLE");

    return S_OK;
}

void Title::Release()
{

}

void Title::Update(float deltaTime)
{
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

    lpBackBuffer->Render(hdc);
}
