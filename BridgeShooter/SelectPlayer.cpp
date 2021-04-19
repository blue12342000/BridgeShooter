#include "SelectPlayer.h"
#include "Image.h"

HRESULT SelectPlayer::Init()
{
	lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");

	lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");

	vLpPlayerImg.resize((int)DataManager::CHARACTER_CODE::NONE);
	for (int i = 0; i < (int)DataManager::CHARACTER_CODE::NONE; ++i)
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

	selectBox = { 50, 500, 150, 600 };
	hasSelected = false;

	return S_OK;
}

void SelectPlayer::Release()
{
	//이 부분 없어도 릴리즈 다 되는걸까
	for (int i = 0; i < vLpPlayerImg.size(); ++i)
	{
		vLpPlayerImg[i] = nullptr;
	}
	vLpPlayerImg.clear();
}

void SelectPlayer::Update(float deltaTime)
{
	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_SPACE))
	{
		if (hasSelected == true)
		{
  			SceneManager::GetSingleton()->ChangeScene();
		}
			
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('A'))
	{
		selectBox.left -= 200;
		selectBox.right -= 200;
		if (selectBox.left <= 50)
		{
			selectBox.left = 50;
			selectBox.right = 150;
		}
		selectIndex--;
		if (selectIndex <= 0) selectIndex = 0;
		
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('D'))
	{
		selectBox.left += 200;
		selectBox.right += 200;
		if (selectBox.left >= 450)
		{
			selectBox.left = 450;
			selectBox.right = 550;
		}	
		selectIndex++;
		if (selectIndex >= 2) selectIndex = 2;
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('S'))
	{
		if (selectIndex == 0)
		{
			DataManager::GetSingleton()->SetCharacter(DataManager::CHARACTER_CODE::YELLOW);
			hasSelected = true;
		}
		if (selectIndex == 1)
		{
			DataManager::GetSingleton()->SetCharacter(DataManager::CHARACTER_CODE::RED);
			hasSelected = true;
		}
		if (selectIndex == 2)
		{
			DataManager::GetSingleton()->SetCharacter(DataManager::CHARACTER_CODE::GRAY);
			hasSelected = true;
		}
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
	Rectangle(hBackDC, selectBox.left, selectBox.top, selectBox.right, selectBox.bottom);

	lpBackBuffer->Render(hdc);
}
