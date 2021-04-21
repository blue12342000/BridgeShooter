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
}

void Ending::Render(HDC hdc)
{
    if (lpEnding)
        lpEnding->Render(hdc);
}
