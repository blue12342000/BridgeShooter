#include "AlienRed.h"
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

void AlienRed::Init()
{
	lpAnimation = new Animation();
	elapsedTime = 0;
	angle = 0;
	collider.SetHitBox(pos, 50, 50);
	lpAnimation->Change("Enemy_4", 4, true);
	lpFactory = new SineFactory();
	lpPattern = new ReflectPattern();
	transform.speed = 80.0;
	hp = 500;
	moveAngle = 0;
	shootAngle = PI / 2.0f;
	pos = { WINSIZE_WIDTH + 100,float(rand() % 200 + 100) };
	shootDuration = 500;
	lpFactory->Init();
	lpFactory->SetCheckTime(shootDuration);
	lpFactory->SetCreateLine(1);
}

void AlienRed::Update(float deltaTime)
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
	}
}

void AlienRed::Render(HDC hdc)
{
	Unit::Render(hdc);
}
