#include "Planet_KMS.h"
#include"BasicFactory.h"
#include"BoomerangFactory.h"
#include"SineFactory.h"
#include"Image.h"
#include"Missile.h"
void Planet_KMS::Init()
{
	state = UNIT_STATE::IDLE;
	lpImage = ImageManager::GetSingleton()->FindImage("Planet_KMS");
	speed = 0;
	elapsedTime = 0;
	motionTimer = 0;
	motionSpeed = 12;
	angle = PI / 2;
	lpFactory = new BoomerangFactory();
	lpFactory->Init();
	frame = 0;
	attack1Timer = 0.0;
}
struct TimeSet
{
	float attack1 = 5.0;
};
void Planet_KMS::Update(float deltaTime)
{
	TimeSet timeset;
	if (lpImage&&this)
	{
		//this->Fire();
		//this->Update(deltaTime);
		motionTimer += (deltaTime * motionSpeed);
		attack1Timer += deltaTime;
		if (attack1Timer >= deltaTime) {
			attack1Timer -= deltaTime;
			//this->Fire();
		}
		if (motionTimer > 1.0f)
		{
			frame += (int)motionTimer;
			frame %= lpImage->GetTotalFrame();
			motionTimer -= (int)motionTimer;
		}
		
	}
	elapsedTime += deltaTime;

}

void Planet_KMS::Release()
{
	
}

void Planet_KMS::Render(HDC hdc)
{
	if (this) {
		Unit::Render(hdc);
	}
}
