#include "Planet_KMS.h"
#include"BasicFactory.h"
#include"BoomerangFactory.h"
#include"HomingFactory.h"
#include"SineFactory.h"
#include"Image.h"

void Planet_KMS::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("Planet_KMS");
	speed = 0;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = -PI / 2;
	lpFactory = new BasicFactory();
	frame = 0;
}

void Planet_KMS::Update(float deltaTime)
{
	if (lpImage&&this)
	{
		motionTimer += (deltaTime * motionSpeed);
		if (motionTimer > 1.0f)
		{
			frame += (int)motionTimer;
			frame %= lpImage->GetTotalFrame();
			motionTimer -= (int)motionTimer;
		}
	}
	elapsedTime += deltaTime;

}

void Planet_KMS::Release()
{
	
}

void Planet_KMS::Render(HDC hdc)
{
	if (this) {
		Unit::Render(hdc);
	}
}
