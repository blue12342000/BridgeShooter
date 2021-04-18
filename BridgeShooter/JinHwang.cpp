#include "JinHwang.h"
#include "JinHwangFactory.h"
#include "Animation.h"

void JinHwang::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("JINHWANG", 50, true);
	speed = 0;
	elapsedTime = 0;
	angle = PI / 2;
	lpFactory = new JinHwangFactory();
	lpFactory->Init();
	collider.SetHitBox(pos, { 0, 0 }, 100, 100);
}

void JinHwang::Update(float deltaTime)
{
	Fire();

	lpFactory->Update(deltaTime);
	lpAnimation->Update(deltaTime);
	collider.SetHitBox(pos);
	elapsedTime += deltaTime;
}

void JinHwang::Render(HDC hdc)
{
	Unit::Render(hdc);
}
