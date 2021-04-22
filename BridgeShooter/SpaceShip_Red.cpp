#include "SpaceShip_Red.h"
#include "Animation.h"
#include "SineFactory.h"

void SpaceShip_Red::Init()
{
	hp = U_MAX_PLAYER_HP;
	maxHp = U_MAX_PLAYER_HP;
	lpAnimation = new Animation();
	lpAnimation->Change("SPACESHIP_RED", 10, true);
	transform.speed = 350;
	elapsedTime = 0;
	angle = -PI / 2;
	SetFactory(new SineFactory());
	collider.SetHitBox(pos, 20, 20);
	force = { 0, 0 };

	lpHitBoxAni = new Animation();
	lpHitBoxAni->Change("HitBox", 12, true);
}

void SpaceShip_Red::Release()
{
	Unit::Release();
	delete lpHitBoxAni;
	lpHitBoxAni = nullptr;
}

void SpaceShip_Red::Update(float deltaTime)
{
	Unit::Update(deltaTime);
	if (lpHitBoxAni) lpHitBoxAni->Update(deltaTime);
}

void SpaceShip_Red::Render(HDC hdc)
{
	Unit::Render(hdc);
	if (lpHitBoxAni) lpHitBoxAni->Render(hdc, pos.x, pos.y);
}
