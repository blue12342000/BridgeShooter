#include "JinHwang.h"
#include "JinHwangFactory.h"
#include "Animation.h"
#include "BasicPattern.h"

void JinHwang::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("JINHWANG", 50, true);
	speed = 420;
	elapsedTime = 0;
	angle = PI / 2;
	lpFactory = new JinHwangFactory();
	lpFactory->Init();
	collider.SetHitBox(pos, { 0, 0 }, 100, 100);
}

void JinHwang::Update(float deltaTime)
{
	Fire();

	Unit::Update(deltaTime);
}

void JinHwang::Render(HDC hdc)
{
	Unit::Render(hdc);
}
