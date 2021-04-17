#include "SpaceShip.h"
#include "Image.h"
#include "BasicFactory.h"
#include "SineFactory.h"

void SpaceShip::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("JINHWANG");
	speed = 200;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 40;
	angle = -PI / 2;

	SetFactory(new BasicFactory());
}

void SpaceShip::Update(float deltaTime)
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("JINHWANG");

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
		lpFactory = new BasicFactory();
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne('2'))
	{
		lpFactory = new SineFactory();
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
