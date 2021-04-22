#include "AlienGreen.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"
#include "BasicFactory.h"
#include "BasicPattern.h"


void AlienGreen::Init()
{
	if (!lpAnimation) lpAnimation = new Animation();
	lpAnimation->Change("Enemy_3", 4, true, true);
	if (!lpFactory) SetFactory(new BasicFactory());
	lpFactory->SetCreateLine(1);
	lpFactory->ResetTimer();
	if (!lpPattern) lpPattern = new BasicPattern();
	elapsedTime = 0;
	angle = PI /2;
	transform.speed = 80.0f;
	hp = U_MAX_ENEMY_HP;
	maxHp = U_MAX_ENEMY_HP;
	pos = { (float)(rand() % (WINSIZE_WIDTH - 50)) + 25.0f, 0.0f - 100.0f };
	collider.SetHitBox(pos, 50, 50);
}

void AlienGreen::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void AlienGreen::Release()
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

void AlienGreen::Render(HDC hdc)
{
	Unit::Render(hdc);
}
