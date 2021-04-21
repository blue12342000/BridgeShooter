#include "AlienGreen.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"
#include "RainFactory.h"
#include "SineFactory.h"
#include "Planet04Factory.h"
#include "BasicPattern.h"


void AlienGreen::Init()
{
	if (lpAnimation)
	{
		delete lpAnimation;
	}
	if (lpPattern)
	{
		delete lpPattern;
	}
	SetFactory(new SineFactory());
	lpAnimation = new Animation();
	lpPattern = new BasicPattern();

	elapsedTime = 0;
	angle = 0;
	collider.SetHitBox(pos, 50, 50);
	lpAnimation->Change("Enemy_3", 4, true);
	lpFactory = new Planet04Factory();
	lpPattern = new BasicPattern();
	transform.speed = 80.0f;
	hp = U_MAX_ENEMY_HP;
	maxHp = U_MAX_ENEMY_HP;
	moveAngle = PI / 2.0f;
	shootAngle = PI / 2.0f;
	pos = { (float)(rand() % ((WINSIZE_WIDTH - 50) - 50 - 1) + 50),0.0f - 100.0f };
	shootDuration = 2000;
	lpFactory->Init();
	lpFactory->SetCheckTime(shootDuration);
	lpFactory->SetCreateLine(1);
}

void AlienGreen::Update(float deltaTime)
{
	if (lpFactory && lpFactory->IsCheckTime(shootDuration))
	{
		angle = shootAngle;
		Fire();
		shootAngle = angle;
	}
	if (lpAnimation)
	{
		lpAnimation->Update(deltaTime);
	}
	if (lpPattern)
	{
		angle = moveAngle;
		Unit::Update(deltaTime);
		lpPattern->Move(deltaTime, this);
		moveAngle = angle;
	}
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
