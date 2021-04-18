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
}

void JinHwang::Update(float deltaTime)
{
	Fire();

	lpAnimation->Update(deltaTime);
	collider.SetHitBox(pos, 100, 100);
	elapsedTime += deltaTime;
}

void JinHwang::Render(HDC hdc)
{
	Unit::Render(hdc);
}
