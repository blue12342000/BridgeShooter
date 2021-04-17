#include "SpaceShip.h"
#include "Image.h"
#include "BasicFactory.h"
#include "SineFactory.h"
#include "RainFactory.h"
#include "BoomerangFactory.h"

void SpaceShip::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("SPACESHIP_IDLE");
	speed = 200;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 20;
	angle = -PI / 2;

	SetFactory(new BasicFactory());
}

void SpaceShip::Update(float deltaTime)
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("SPACESHIP_IDLE");

	if (KeyManager::GetSingleton()->IsKeyDownStay('W'))
	{
		pos.y -= speed * deltaTime;
	}

	if (KeyManager::GetSingleton()->IsKeyDownStay('S'))
	{
		pos.y += speed * deltaTime;
	}

	if (KeyManager::GetSingleton()->IsKeyDownStay('A'))
	{
		lpImage = ImageManager::GetSingleton()->FindImage("SPACESHIP_LEFT");
		pos.x -= speed * deltaTime;
		
		state = UNIT_STATE::MOVE_LEFT;
	}

	if (KeyManager::GetSingleton()->IsKeyDownStay('D'))
	{
		lpImage = ImageManager::GetSingleton()->FindImage("SPACESHIP_RIGHT");
		pos.x += speed * deltaTime;
		state = UNIT_STATE::MOVE_RIGHT;
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

	if (KeyManager::GetSingleton()->IsKeyDownStay(VK_SPACE))
	{
		Fire();
	}

	if (lpImage)
	{
		motionTimer += (deltaTime * motionSpeed);
		if (motionTimer > 1)
		{
			frame += (int)motionTimer;
			frame %= lpImage->GetTotalFrame();
			motionTimer -= (int)motionTimer;
		}
	}
	elapsedTime += deltaTime;
}

void SpaceShip::Release()
{
}

void SpaceShip::Render(HDC hdc)
{
	Unit::Render(hdc);
}
