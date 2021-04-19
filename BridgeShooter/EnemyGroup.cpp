#include "EnemyGroup.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "BasicFactory.h"
#include "BasicPattern.h"

void EnemyGroup::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("JINHWANG", 50, true);
	lpPattern = new BasicPattern();
	elapsedTime = 0;
	angle = 0;
	moveAngle = 0;
	speed = 50.0;
	shootAngle = PI / 2.0f;
	collider.SetHitBox(pos, { 0, 0 }, 50, 50);
}

void EnemyGroup::Update(float deltaTime)
{
	if (lpFactory) 
	{
		angle = shootAngle;
		Fire();
		lpFactory->Update(deltaTime);
		shootAngle = angle;
	}
	if (lpAnimation) 
	{
		lpAnimation->Update(deltaTime);
	}
	if (lpPattern)
	{
		angle = moveAngle;
		lpPattern->Move(deltaTime, this);
		moveAngle = angle;
	}
	collider.SetHitBox(pos);
	elapsedTime += deltaTime;
}

void EnemyGroup::Render(HDC hdc)
{
	Unit::Render(hdc);
}

void EnemyGroup::Release()
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
	}
}

