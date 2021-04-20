#include "SpaceShip.h"
#include "Animation.h"
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"
#include "Planet_KMS_Factory.h"
#include "BoomerangPattern.h"
#include "SSJFactory.h"
#include "JinHwangFactory.h"
#include "SpaceShipFactory.h"
#include "HPgauge.h"

void SpaceShip::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_IDLE", 20, true);
	speed = 200;
	hp = 200;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 0;
	isBombUsed = false;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, { 0,0 }, 20, 20);
}

void SpaceShip::Update(float deltaTime)
{
	if (force.x > 0)
	{
		lpAnimation->Change("SPACESHIP_RIGHT", 20, true);
	}
	else if (force.x < 0)
	{
		lpAnimation->Change("SPACESHIP_LEFT", 20, true);
	}
	else
	{
		lpAnimation->Change("SPACESHIP_IDLE", 20, true);
	}

	if (KeyManager::GetSingleton()->IsKeyDownOne('1'))
	{
		SetFactory(new BasicFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('2'))
	{
		SetFactory(new SineFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('3'))
	{
		//여기서 봄 키 입력 테스트 해보고 싶다.
		lphpGauge->IsBombUsed(deltaTime);
		//SetFactory(new RainFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('4'))
	{
		SetFactory(new Planet_KMS_Factory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('5'))
	{
		SetFactory(new SSJFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('6'))
	{
		SetFactory(new JinHwangFactory());
	}

	Unit::Update(deltaTime);
}

void SpaceShip::Render(HDC hdc)
{
	Unit::Render(hdc);
}
