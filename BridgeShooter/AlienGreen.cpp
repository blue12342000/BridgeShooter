#include "AlienGreen.h"
//기본 라이브러리(필수)
#include "Factory.h"
#include "Animation.h"
#include "Pattern.h"
#include "GameObject.h"

//쏘는 팩토리 라이브러리
#include "BasicFactory.h"
#include "SineFactory.h"
#include "Planet04Factory.h"
#include "RainFactory.h"
#include "JinHwangFactory.h"

//움직이는 패턴 라이브러리
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "GuidePattern.h"
#include "SinePattern.h"
#include "SpiralPattern.h"

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
	SetFactory(new Planet04Factory());
	lpAnimation = new Animation();
	lpPattern = new BasicPattern();

	elapsedTime = 0;
	angle = 0;
	collider.SetHitBox(pos, { 0, 0 }, 50, 50);
	lpAnimation->Change("Enemy_3", 4, true);
	speed = 80.0f;
	hp = 50;
	moveAngle = PI / 2.0f;
	shootAngle = PI / 2.0f;
	pos = { (float)(rand() % ((WINSIZE_WIDTH - 50) - 50 - 1) + 50),0.0f - 100.0f };
	shootDuration = 200;
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
