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
#include "UIobject.h"

void SpaceShip::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_IDLE", 20, true);
	transform.speed = 200;
	hp = U_MAX_PLAYER_HP;
	maxHp = U_MAX_PLAYER_HP;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 1;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, 20, 20);
	force = { 0, 0 };
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

	Unit::Update(deltaTime);
}

void SpaceShip::Render(HDC hdc)
{
	Unit::Render(hdc);
}
