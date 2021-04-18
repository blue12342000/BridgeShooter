#include "Animation.h"
#include "Image.h"

void Animation::Change(string imageKey, int fps, bool isLoop)
{
	if (lpImage)
	{
		Image* lpTempImage = ImageManager::GetSingleton()->FindImage(imageKey);
		if (lpImage != lpTempImage)
		{
			lpImage = lpTempImage;
			this->isLoop = isLoop;
			this->fps = fps;
			frame = 0;
		}
	}
	else
	{
		lpImage = ImageManager::GetSingleton()->FindImage(imageKey);
		this->isLoop = isLoop;
		this->fps = fps;
		frame = 0;
	}
}

void Animation::Update(float deltaTime)
{
	frame += (deltaTime * fps);
	if ((int)frame >= lpImage->GetTotalFrame())
	{
		if (isLoop)
		{
			frame -= ((int)(frame / lpImage->GetTotalFrame())) * lpImage->GetTotalFrame();
		}
		else
		{
			frame = lpImage->GetTotalFrame() - 1;
		}
	}
}

void Animation::Render(HDC hdc, int destX, int destY)
{
	lpImage->Render(hdc, destX, destY, ((int)frame), U_IA_CENTER);
}
