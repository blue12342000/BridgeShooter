#include "Planet_SSJ.h"
#include "Animation.h"
#include "SSJFactory.h"	

void Planet_SSJ::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("PLANET_SSJ", 50, true);
	transform.speed = 100;
	hp = U_MAX_BOSS_HP;
	maxHp = U_MAX_BOSS_HP;
	elapsedTime = 0;
	angle = /*-PI / 2*/0;
	lpFactory = new SSJFactory();	
	lpFactory->Init();
	collider.SetHitBox(pos, 100, 100);
}

void Planet_SSJ::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void Planet_SSJ::Render(HDC hdc)
{
	Unit::Render(hdc);
}
