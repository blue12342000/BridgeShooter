#include "Planet_KMS.h"
#include"BasicFactory.h"
#include"BoomerangFactory.h"
#include"SineFactory.h"
#include"Animation.h"
#include"Missile.h"
void Planet_KMS::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("Planet_KMS", 50, true);
	speed = 0;
	elapsedTime = 0;
	angle = PI / 2;
	lpFactory = new BoomerangFactory();
	lpFactory->Init();
	attack1Timer = 0.0;
}

void Planet_KMS::Update(float deltaTime)
{
	lpAnimation->Update(deltaTime);
	Fire();
	elapsedTime += deltaTime;
}

void Planet_KMS::Render(HDC hdc)
{
	Unit::Render(hdc);
}
