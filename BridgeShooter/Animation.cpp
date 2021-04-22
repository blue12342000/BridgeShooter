#include "Animation.h"
#include "Image.h"

void Animation::Change(string imageKey, int fps, bool isLoop, bool isReset)
{
	if (isReset)
	{
		lpImage = ImageManager::GetSingleton()->FindImage(imageKey);
		this->imageKey = imageKey;
		this->isLoop = isLoop;
		this->fps = fps;
		frame = 0;
	}
	else
	{
		if (lpImage)
		{
			if (this->imageKey != imageKey)
			{
				lpImage = ImageManager::GetSingleton()->FindImage(imageKey);
				this->imageKey = imageKey;
				this->isLoop = isLoop;
				this->fps = fps;
				frame = 0;
			}
		}
		else
		{
			lpImage = ImageManager::GetSingleton()->FindImage(imageKey);
			this->imageKey = imageKey;
			this->isLoop = isLoop;
			this->fps = fps;
			frame = 0;
		}
	}
}

void Animation::Update(float deltaTime)
{
	frame += deltaTime * (float)fps;
	if (frame >= lpImage->GetTotalFrame())
	{
		if (isLoop)
		{
			frame -= ((int)(frame / lpImage->GetTotalFrame()) * lpImage->GetTotalFrame());
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

void Animation::Render(HDC hdc, int destX, int destY, float angle)
{
	lpImage->RotateRender(hdc, destX, destY, angle, ((int)frame));
}
