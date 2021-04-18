#include "Planet04.h"	//배용진 행성
#include "Planet04Factory.h"
#include "Image.h"

void Planet04::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("Planet04");
	speed = 0;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = PI / 2;
	lpFactory = new Planet04Factory();
	lpFactory->Init();
}

void Planet04::Update(float deltaTime)
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("Planet04");

	fireTimer += deltaTime;
	if (fireTimer > 0.01f)
	{
		fireTimer = 0;
		Fire();
	}

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

void Planet04::Release()
{
}

void Planet04::Render(HDC hdc)
{
	Unit::Render(hdc);
}
