#include "SpaceShip.h"
#include "Animation.h"
#include "SpaceShipFactory.h"

void SpaceShip::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_IDLE", 20, true);
	transform.speed = 350;
	hp = U_MAX_PLAYER_HP;
	maxHp = U_MAX_PLAYER_HP;
	elapsedTime = 0;
	angle = -PI / 2;
	SetFactory(new SpaceShipFactory());
	collider.SetHitBox(pos, 20, 20);
	force = { 0, 0 };

	lpHitBoxAni = new Animation();
	lpHitBoxAni->Change("HitBox", 12, true);
}

void SpaceShip::Release()
{
	Unit::Release();
	delete lpHitBoxAni;
	lpHitBoxAni = nullptr;
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
	if (lpHitBoxAni) lpHitBoxAni->Update(deltaTime);
}

void SpaceShip::Render(HDC hdc)
{
	Unit::Render(hdc);
	if (lpHitBoxAni) lpHitBoxAni->Render(hdc, pos.x, pos.y);
}
