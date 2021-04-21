#include "SpaceShip_Gray.h"
#include "Animation.h"
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"
#include "BoomerangPattern.h"
#include "SSJFactory.h"
#include "JinHwangFactory.h"
#include "SpaceShipFactory.h"
#include "Planet_KMS_Factory.h"

#include "UIobject.h"

void SpaceShip_Gray::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_GRAY", 10, true);
	transform.speed = 200;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 0;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, 30, 30);
}

void SpaceShip_Gray::Update(float deltaTime)
{

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
		//lphpGauge->IsBombUsed(deltaTime);
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

void SpaceShip_Gray::Render(HDC hdc)
{
	Unit::Render(hdc);
}
