#include "SpaceShip_Red.h"
#include "Animation.h"
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"
#include "BoomerangPattern.h"
#include "SSJFactory.h"
#include "JinHwangFactory.h"
#include "SpaceShipFactory.h"
#include "Planet_KMS_Factory.h"

void SpaceShip_Red::Init()
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

void SpaceShip_Red::Update(float deltaTime)
{
	input = INPUT_TYPE3::NONE;
	if (KeyManager::GetSingleton()->IsKeyDownStay('W'))
	{
		pos.y -= speed * deltaTime;
		input = INPUT_TYPE3::UP;
	}

	if (KeyManager::GetSingleton()->IsKeyDownStay('S'))
	{
		pos.y += speed * deltaTime;
		input = INPUT_TYPE3::DOWN;
	}

	if (KeyManager::GetSingleton()->IsKeyDownOne('A'))
	{
		lpAnimation->Change("SPACESHIP_LEFT", 20, true);
		input = INPUT_TYPE3::LEFT;
	}
	else if (KeyManager::GetSingleton()->IsKeyDownStay('A'))
	{
		input = INPUT_TYPE3::LEFT;
		pos.x -= speed * deltaTime;
	}

	if (KeyManager::GetSingleton()->IsKeyDownOne('D'))
	{
		input = INPUT_TYPE3::RIGHT;
		lpAnimation->Change("SPACESHIP_RIGHT", 20, true);
	}
	else if (KeyManager::GetSingleton()->IsKeyDownStay('D'))
	{
		input = INPUT_TYPE3::RIGHT;
		pos.x += speed * deltaTime;
	}

	switch (input)
	{
	case INPUT_TYPE3::UP:
	case INPUT_TYPE3::DOWN:
	case INPUT_TYPE3::NONE:
		lpAnimation->Change("SPACESHIP_IDLE", 20, true);
		break;
	}

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

	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_SPACE))
	{
		Fire();
	}

	collider.SetHitBox(pos);
	lpFactory->Update(deltaTime);
	lpAnimation->Update(deltaTime);
	elapsedTime += deltaTime;
}

void SpaceShip_Red::Render(HDC hdc)
{
	Unit::Render(hdc);
}
