#include "JinHwang.h"
#include "BasicFactory.h"
#include "Image.h"

void JinHwang::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("JINHWANG");
	speed = 0;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = PI / 2;
	lpFactory = new BasicFactory();
	lpFactory->Init();
}

void JinHwang::Update(float deltaTime)
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("JINHWANG");

	fireTimer += deltaTime;
	if (fireTimer > 0.2f)
	{
		fireTimer = 0;
		//Fire();
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

void JinHwang::Release()
{
}

void JinHwang::Render(HDC hdc)
{
	Unit::Render(hdc);
}
