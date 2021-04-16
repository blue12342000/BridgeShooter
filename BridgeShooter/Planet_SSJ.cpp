#include "Planet_SSJ.h"
#include "Image.h"
#include "BasicFactory.h"	//일단 실험용

void Planet_SSJ::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("PLANET_SSJ");
	speed = 200;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = -PI / 2;
	lpFactory = new BasicFactory();	//일단 실험용
	frame = 50;
}

void Planet_SSJ::Update(float deltaTime)
{
	if (lpImage)
	{
		motionTimer += (deltaTime * motionSpeed);
		if (motionTimer > 1)
		{
			frame += (int)motionTimer;
			frame %= lpImage->GetTotalFrame();
			motionTimer -= (int)motionTimer;
		}
	}
	elapsedTime += deltaTime;
}

void Planet_SSJ::Release()
{
}

void Planet_SSJ::Render(HDC hdc)
{
	Unit::Render(hdc);
}
