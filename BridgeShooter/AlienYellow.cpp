#include "AlienYellow.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"
#include "BasicFactory.h"
#include "ReflectPattern.h"

void AlienYellow::Init()
{
	if (!lpAnimation) lpAnimation = new Animation();
	lpAnimation->Change("Enemy_2", 4, true, true);
	if (!lpFactory) SetFactory(new BasicFactory());
	lpFactory->SetCreateLine(0);
	lpFactory->ResetTimer();
	if (!lpPattern) lpPattern = new ReflectPattern();
	elapsedTime = 0;

	angle = PI;
	transform.speed = 80.0f;
	hp = U_MAX_ENEMY_HP;
	maxHp = U_MAX_ENEMY_HP;
	pos = { WINSIZE_WIDTH + 25.0f, (float)(rand() % 200) };
	collider.SetHitBox(pos, 50, 50);
}

void AlienYellow::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void AlienYellow::Release()
{
	if (lpAnimation)
	{
		delete lpAnimation;
		lpAnimation = nullptr;
	}
	if (lpFactory)
	{
		lpFactory->Release();
		delete lpFactory;
		lpFactory = nullptr;
	}
	if (lpPattern)
	{
		delete lpPattern;
		lpPattern = nullptr;
	}
}

void AlienYellow::Render(HDC hdc)
{
	Unit::Render(hdc);
}
