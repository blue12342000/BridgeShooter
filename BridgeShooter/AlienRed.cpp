#include "AlienRed.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"
#include "BasicFactory.h"
#include "ReflectPattern.h"

void AlienRed::Init()
{
	if (!lpAnimation) lpAnimation = new Animation();
	lpAnimation->Change("Enemy_4", 4, true, true);
	if (!lpFactory) SetFactory(new BasicFactory());
	lpFactory->SetCreateLine(1);
	lpFactory->ResetTimer();
	elapsedTime = 0;
	if (!lpPattern) lpPattern = new ReflectPattern();
	angle = 0;
	transform.speed = 80.0;
	hp = U_MAX_ENEMY_HP;
	maxHp = U_MAX_ENEMY_HP;
	pos = { WINSIZE_WIDTH + 100,float(rand() % 200 + 100) };
	collider.SetHitBox(pos, 50, 50);
}

void AlienRed::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void AlienRed::Release()
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

void AlienRed::Render(HDC hdc)
{
	Unit::Render(hdc);
}
