#include "SpaceShip.h"
#include "Animation.h"
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"
#include "BoomerangFactory.h"
#include "BoomerangPattern.h"
#include "SSJFactory.h"
#include "JinHwangFactory.h"

void SpaceShip::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_IDLE", 20, true);
	speed = 200;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 0;
	SetFactory(new BasicFactory());
}

void SpaceShip::Update(float deltaTime)
{
	input = INPUT_TYPE::NONE;
	if (KeyManager::GetSingleton()->IsKeyDownStay('W'))
	{
		pos.y -= speed * deltaTime;
		input = INPUT_TYPE::UP;
	}

	if (KeyManager::GetSingleton()->IsKeyDownStay('S'))
	{
		pos.y += speed * deltaTime;
		input = INPUT_TYPE::DOWN;
	}

	if (KeyManager::GetSingleton()->IsKeyDownOne('A'))
	{
		lpAnimation->Change("SPACESHIP_LEFT", 20, true);
		input = INPUT_TYPE::LEFT;
	}
	else if (KeyManager::GetSingleton()->IsKeyDownStay('A'))
	{
		input = INPUT_TYPE::LEFT;
		pos.x -= speed * deltaTime;
	}

	if (KeyManager::GetSingleton()->IsKeyDownOne('D'))
	{
		input = INPUT_TYPE::RIGHT;
		lpAnimation->Change("SPACESHIP_RIGHT", 20, true);
	}
	else if (KeyManager::GetSingleton()->IsKeyDownStay('D'))
	{
		input = INPUT_TYPE::RIGHT;
		pos.x += speed * deltaTime;
	}

	switch (input)
	{
	case INPUT_TYPE::UP:
	case INPUT_TYPE::DOWN:
	case INPUT_TYPE::NONE:
		lpAnimation->Change("SPACESHIP_IDLE", 20, true);
		break;
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
		SetFactory(new RainFactory());
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('4'))
	{
		SetFactory(new BoomerangFactory());
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

	lpAnimation->Update(deltaTime);
	collider.SetHitBox(pos, 30, 30);
	elapsedTime += deltaTime;
}

void SpaceShip::Render(HDC hdc)
{
	Unit::Render(hdc);
}
