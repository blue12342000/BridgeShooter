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
	hp = U_MAX_PLAYER_HP;
	maxHp = U_MAX_PLAYER_HP;
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_GRAY", 10, true);
	transform.speed = 300;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 0;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, 30, 30);
	force = { 0, 0 };
}

void SpaceShip_Gray::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void SpaceShip_Gray::Render(HDC hdc)
{
	Unit::Render(hdc);
}
