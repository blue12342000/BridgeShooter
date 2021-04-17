#include "Planet.h"
#include "Image.h"
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"


void Planet::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("Planet04");
	speed = 0;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = -PI / 2;
	lpFactory = new BasicFactory();
}

void Planet::Update(float deltaTime)
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("Planet04");

	
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

void Planet::Release()
{
}

void Planet::Render(HDC hdc)
{
	Unit::Render(hdc);
}
