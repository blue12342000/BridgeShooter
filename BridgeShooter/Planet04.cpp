#include "Planet04.h"
#include "Planet04Factory.h"
#include "Animation.h"

void Planet04::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("Planet04", 50, true);
	transform.speed = 50;
	hp = 500;
	bomb = 3;
	elapsedTime = 0;
	angle = PI / 2;
	lpFactory = new Planet04Factory();
	lpFactory->Init();
	collider.SetHitBox(pos, 180, 180);	//init 에서 수치
}

void Planet04::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void Planet04::Render(HDC hdc)
{
	Unit::Render(hdc);
}
