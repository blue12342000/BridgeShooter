#include "SelectPlayer.h"
#include "Image.h"

HRESULT SelectPlayer::Init()
{
	lpBackImage = ImageManager::GetSingleton()->FindImage("SPACE");
	lpBackBuffer = ImageManager::GetSingleton()->FindImage("BACKBUFFER");
	lpSelctInfo = ImageManager::GetSingleton()->FindImage("SELECT_INFO");

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

	selectBox = { 30, 400, 180, 600 };
	selectIndex = 0;
	maxIndex = vLpPlayerImg.size()-1;
	hasSelected = false;

	return S_OK;
}

void SelectPlayer::Release()
{

}

void SelectPlayer::Update(float deltaTime)
{
	if (hasSelected == false)
	{
		for (int i = '1'; i < '1' + 4; ++i)
		{
			if (KeyManager::GetSingleton()->IsKeyDownOne(i))
			{
				hasSelected = true;
				DataManager::GetSingleton()->SetCharacter((DataManager::CHARACTER_CODE)(i - '1' + 4));
			}
		}

		if (KeyManager::GetSingleton()->IsKeyDownOne('A'))
		{
			selectBox.left -= 200;
			selectBox.right -= 200;
			if (selectBox.left <= 30)
			{
				selectBox.left = 30;
				selectBox.right = 180;
			}
			selectIndex--;
			if (selectIndex <= 0) selectIndex = 0;

		}
		if (KeyManager::GetSingleton()->IsKeyDownOne('D'))
		{
			selectBox.left += 200;
			selectBox.right += 200;
			if (selectBox.left >= 430)
			{
				selectBox.left = 430;
				selectBox.right = 580;
			}
			selectIndex++;
			if (selectIndex >= maxIndex) selectIndex = maxIndex;
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
	
	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_RETURN))
	{
		if (hasSelected == true)
		{
			SceneManager::GetSingleton()->ChangeScene(SceneManager::SCENE_STATE::INGAME);
		}
	}
}

void SelectPlayer::Render(HDC hdc)
{
	HDC hBackDC = lpBackBuffer->GetMemDC();
	lpBackImage->Render(hBackDC);
	lpSelctInfo->Render(hBackDC);

	if (!hasSelected)
	{
		HPEN hPen;
		HPEN hOldPen;
		HBRUSH hBr = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH hOldBr = (HBRUSH)SelectObject(hBackDC, hBr);
		hPen = CreatePen(PS_SOLID, 3, RGB(29, 247, 255));
		hOldPen = (HPEN)::SelectObject(hBackDC, (HGDIOBJ)hPen);

		Rectangle(hBackDC, selectBox.left, selectBox.top, selectBox.right, selectBox.bottom);

		hPen = (HPEN)::SelectObject(hBackDC, hOldPen);
		hBr = (HBRUSH)SelectObject(hBackDC, hOldBr);
		DeleteObject(hPen);
		DeleteObject(hBr);
	}
	else if (hasSelected)
	{
		HPEN hPen;
		HPEN hOldPen;
		HBRUSH hBr = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH hOldBr = (HBRUSH)SelectObject(hBackDC, hBr);
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
		hOldPen = (HPEN)::SelectObject(hBackDC, (HGDIOBJ)hPen);

		Rectangle(hBackDC, selectBox.left, selectBox.top, selectBox.right, selectBox.bottom);

		hPen = (HPEN)::SelectObject(hBackDC, hOldPen);
		hBr = (HBRUSH)SelectObject(hBackDC, hOldBr);
		DeleteObject(hPen);
		DeleteObject(hBr);
	}


	for (int i = 0; i < vLpPlayerImg.size(); ++i)
	{
		vLpPlayerImg[i]->Render(hBackDC, 10 + i * 200, 400);
	}



	lpBackBuffer->Render(hdc);
}
