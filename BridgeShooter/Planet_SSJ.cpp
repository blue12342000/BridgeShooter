#include "Planet_SSJ.h"
#include "Image.h"
#include "SSJFactory.h"	

void Planet_SSJ::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("PLANET_SSJ");
	speed = 200;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = -PI / 2;
	lpFactory = new SSJFactory();	
	lpFactory->Init();
	frame = 50;

}

void Planet_SSJ::Update(float deltaTime)
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("PLANET_SSJ");

	Fire();

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
	if (lpFactory) delete lpFactory; lpFactory = nullptr; 
}

void Planet_SSJ::Render(HDC hdc)
{
	Unit::Render(hdc);
}
