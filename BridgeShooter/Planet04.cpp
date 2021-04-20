#include "Planet04.h"
#include "Planet04Factory.h"
#include "Animation.h"

void Planet04::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("Planet04", 50, true);
	speed = 20;
	hp = 500;
	elapsedTime = 0;
	angle = PI / 2;
	lpFactory = new Planet04Factory();
	lpFactory->Init();
	collider.SetHitBox(pos, { 0,0 },180, 180);	//init 에서 수치
}

void Planet04::Update(float deltaTime)
{
	Fire();

	Unit::Update(deltaTime);
  //lpFactory->Update(deltaTime);
  //lpAnimation->Update(deltaTime);
  //collider.SetHitBox(pos);	//업데이트에서 수치
  //elapsedTime += deltaTime;
}

void Planet04::Render(HDC hdc)
{
	Unit::Render(hdc);
}
