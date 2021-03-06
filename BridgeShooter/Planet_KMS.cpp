#include "Planet_KMS.h"
#include"BasicFactory.h"
#include"Planet_KMS_Factory.h"
#include"SineFactory.h"
#include"Animation.h"
#include"Missile.h"
void Planet_KMS::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("Planet_KMS", 50, true);
	hp = U_MAX_BOSS_HP;
	maxHp = U_MAX_BOSS_HP;
	transform.speed = 100;
	elapsedTime = 0;
	angle =PI*2.0f/3.0f;
	lpFactory = new Planet_KMS_Factory();
	lpFactory->Init();
	collider.SetHitBox(pos, 100, 100);

}

void Planet_KMS::Update(float deltaTime)
{

	Unit::Update(deltaTime);
}

void Planet_KMS::Render(HDC hdc)
{
	Unit::Render(hdc);
}
