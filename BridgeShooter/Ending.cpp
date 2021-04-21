#include "Ending.h"
#include "Image.h"
#include "BridgeShooter.h"

HRESULT Ending::Init()
{
    lpEnding = ImageManager::GetSingleton()->FindImage("ENDING");


    return S_OK;
}

void Ending::Release()
{
}

void Ending::Update(float deltaTime)
{
    if (KeyManager::GetSingleton()->IsKeyDownOne(VK_ESCAPE))
    {
        SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::TITLE);
    }

}

void Ending::Render(HDC hdc)
{
    if (lpEnding)
        lpEnding->Render(hdc);
}
