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

void SpaceShip::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_IDLE", 20, true);
	speed = 200;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 0;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, { 0,0 }, 30, 30);
}

void SpaceShip::Update(float deltaTime)
{
	if (KeyManager::GetSingleton()->IsKeyDownOne('1'))
	{
		SetFactory(new RainFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('2'))
	{
		SetFactory(new SineFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('3'))
	{
//있다가 1번으로 수정이동	//SetFactory(new BasicFactory());
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
	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_OEM_4))
	{
		if (lpFactory) lpFactory->SetCreateLine(--power);
		if (power < 0) power = 0;
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_OEM_6))
	{
		if (lpFactory) lpFactory->SetCreateLine(++power);
		if (power < 0) power = 0;
	}

	Unit::Update(deltaTime);
}

void SpaceShip::Render(HDC hdc)
{
	Unit::Render(hdc);
}
