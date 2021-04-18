#include "Planet04.h"	//배용진 행성
#include "Planet04Factory.h"
#include "Animation.h"

void Planet04::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("Planet04", 50, true);
	speed = 0.0f;
	elapsedTime = 0.0f;
	angle = PI / 2;
	lpFactory = new Planet04Factory();
	lpFactory->Init();
}

void Planet04::Update(float deltaTime)
{
	fireTimer += deltaTime;
	if (fireTimer > 0.001f)
	{
		fireTimer = 0;
		Fire();
	}

	lpAnimation->Update(deltaTime);
	collider.SetHitBox(pos, 180, 180);
	elapsedTime += deltaTime;
}

void Planet04::Render(HDC hdc)
{
	Unit::Render(hdc);
}
