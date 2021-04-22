#include "AlienBlue.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"
#include "BasicFactory.h"
#include "ReflectPattern.h"

void AlienBlue::Init()
{
	if (!lpAnimation) lpAnimation = new Animation();
	lpAnimation->Change("Enemy_1", 4, true, true);
	if (!lpFactory) SetFactory(new BasicFactory());
	lpFactory->SetCreateLine(4);
	if (!lpPattern) lpPattern = new ReflectPattern();
	elapsedTime = 0;
	angle = 0;
	transform.speed = 80.0;
	hp = U_MAX_ENEMY_HP;
	maxHp = U_MAX_ENEMY_HP;
	pos = { 0 - 100, float(rand() % 200 + 100) };
	collider.SetHitBox(pos, 50, 50);
}

void AlienBlue::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void AlienBlue::Release()
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

void AlienBlue::Render(HDC hdc)
{
	Unit::Render(hdc);
}
