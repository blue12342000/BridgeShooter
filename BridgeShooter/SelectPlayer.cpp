#include "SelectPlayer.h"
#include "Image.h"

HRESULT SelectPlayer::Init()
{
	lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");

	lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");

	vLpPlayerImg.resize(3);
	for (int i = 0; i < 3; ++i)
	{
		switch (i)
		{
		case 0:
			vLpPlayerImg[i] = ImageManager::GetSingleton()->FindImage("SELECT_YELLOW");
			break;
		case 1:
			vLpPlayerImg[i] = ImageManager::GetSingleton()->FindImage("SELECT_RED");
			break;
		case 2:
			vLpPlayerImg[i] = ImageManager::GetSingleton()->FindImage("SELECT_GRAY");
			break;
		}
		
	}
	return S_OK;
}

void SelectPlayer::Release()
{
	for (int i = 0; i < vLpPlayerImg.size(); ++i)
	{
		//delete vLpPlayerImg[i];
		//vLpPlayerImg[i] = nullptr;
	}
	vLpPlayerImg.clear();
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

	for (int i = 0; i < vLpPlayerImg.size(); ++i)
	{
		vLpPlayerImg[i]->Render(hBackDC, 50 + i * 200, 500);
	}

	lpBackBuffer->Render(hdc);
}
