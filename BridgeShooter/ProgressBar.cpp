#include "ProgressBar.h"
#include "Image.h"

void ProgressBar::CreateProgressBar(string imageKey)
{
	if (lpImage)
	{
		Image* lpTempImage = ImageManager::GetSingleton()->FindImage(imageKey);
		if (lpImage != lpTempImage)
		{
			lpImage = lpTempImage;
		}
	}
	else
		lpImage = ImageManager::GetSingleton()->FindImage(imageKey);
	//GetRectToCenter(playerMaxHp / 2 / 100 + 50, 100, playerMaxHp / 100, 18);
}

void ProgressBar::Update(float deltaTime)
{
}

void ProgressBar::Render(HDC hdc, int X, int Y)
{
	lpImage->Render(hdc, X, Y, 1, U_IA_CENTER);
}
