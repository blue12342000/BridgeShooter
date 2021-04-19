//기본 라이브러리(필수)
#include "EnemyGroup.h"
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"

//쏘는 팩토리 라이브러리
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"
#include "JinHwangFactory.h"

//움직이는 패턴 라이브러리
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "BoomerangPattern.h"
#include "SinePattern.h"
#include "SpiralPattern.h"

void EnemyGroup::Init()
{
	lpAnimation = new Animation();
	elapsedTime = 0;
	angle = 0;
	collider.SetHitBox(pos, { 0, 0 }, 50, 50);
	enemyKinds = 3; 
	switch (enemyKinds)
	{
	case 1:
		lpAnimation->Change("Enemy_1", 4, true);
		lpFactory = new BasicFactory();
		lpPattern = new ReflectPattern();
		speed = 80.0;
		moveAngle = 0;
		shootAngle = PI / 2.0f;
		pos = { WINSIZE_WIDTH / 2,WINSIZE_HEIGHT / 2 };
		shootDuration = 500;
		break;
	case 2:
		lpAnimation->Change("Enemy_2", 4, true);
		lpFactory = new BasicFactory();
		lpPattern = new BasicPattern();
		speed = 50.0f;
		moveAngle =	 PI / 2.0f;
		shootAngle = PI / 2.0f;
		pos = { WINSIZE_WIDTH/2,WINSIZE_HEIGHT /2};
		shootDuration = 500;
		break;
	case 3:
		lpAnimation->Change("Enemy_3", 4, true);
		lpFactory = new BasicFactory();
		lpPattern = new SpiralPattern();
		speed = 80.0;
		moveAngle = 0;
		shootAngle = PI / 2.0f;
		pos = { WINSIZE_WIDTH / 2,WINSIZE_HEIGHT / 2 };
		shootDuration = 500;
		break;
	case 4:
		lpAnimation->Change("Enemy_4", 4, true);
		lpFactory = new SineFactory();
		lpPattern = new SinePattern();
		speed = 1.0f;
		moveAngle = PI / 3.0f;
		shootAngle = PI / 2.0f;
		pos = { WINSIZE_WIDTH / 2,WINSIZE_HEIGHT / 2 };
		shootDuration = 500;
		break;
	}
	lpFactory->Init();
	lpFactory->SetCheckTime(shootDuration);
}

void EnemyGroup::Update(float deltaTime)
{
	if (lpFactory)
	{
		angle = shootAngle;
		if (lpFactory->IsCheckTime(shootDuration)) 
		{
			Fire();
		}
		
		lpFactory->Update(deltaTime);
		shootAngle = angle;
	}
	if (lpAnimation) 
	{
		lpAnimation->Update(deltaTime);
	}
	if (lpPattern)
	{
		MoveInfo moveinfo;
		angle = moveAngle;
		moveinfo=lpPattern->Move(deltaTime, this);
		angle = moveinfo.angle;
		moveAngle = angle;
		if ((moveinfo.deltaPos.x)|| (moveinfo.deltaPos.y))
		{
			pos.x += moveinfo.deltaPos.x;
			pos.y += moveinfo.deltaPos.y;
		}
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

