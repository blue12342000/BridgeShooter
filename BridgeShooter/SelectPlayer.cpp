#include "SelectPlayer.h"
#include "Image.h"

HRESULT SelectPlayer::Init()
{
	lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");

	lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
	return S_OK;
}

void SelectPlayer::Release()
{
}

void SelectPlayer::Update(float deltaTime)
{
	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene();
	}
}

void SelectPlayer::Render(HDC hdc)
{
	HDC hBackDC = lpBackBuffer->GetMemDC();
	lpBackImage->Render(hBackDC);
	lpBackBuffer->Render(hdc);
}
