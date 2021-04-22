#include "SpaceShip_Gray.h"
#include "Animation.h"
#include "RainFactory.h"

void SpaceShip_Gray::Init()
{
	hp = U_MAX_PLAYER_HP;
	maxHp = U_MAX_PLAYER_HP;
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_GRAY", 10, true);
	transform.speed = 350;
	elapsedTime = 0;
	angle = -PI / 2;
	SetFactory(new RainFactory());
	collider.SetHitBox(pos, 20, 20);
	force = { 0, 0 };

	lpHitBoxAni = new Animation();
	lpHitBoxAni->Change("HitBox", 12, true);
}

void SpaceShip_Gray::Release()
{
	Unit::Release();
	delete lpHitBoxAni;
	lpHitBoxAni = nullptr;
}

void SpaceShip_Gray::Update(float deltaTime)
{
	Unit::Update(deltaTime);
	if (lpHitBoxAni) lpHitBoxAni->Update(deltaTime);
}

void SpaceShip_Gray::Render(HDC hdc)
{
	Unit::Render(hdc);
	if (lpHitBoxAni) lpHitBoxAni->Render(hdc, pos.x, pos.y);
}
