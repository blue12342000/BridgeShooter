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
<<<<<<< Updated upstream
=======
#include "UIobject.h"
>>>>>>> Stashed changes

void SpaceShip_Red::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_RED", 10, true);
	speed = 200;
	elapsedTime = 0;
	angle = -PI / 2;
	power = 0;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, { 0,0 }, 30, 30);
}

void SpaceShip_Red::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void SpaceShip_Red::Render(HDC hdc)
{
	Unit::Render(hdc);
}
