#include "Planet_SSJ.h"
#include "Animation.h"
#include "SSJFactory.h"	

void Planet_SSJ::Init()
{
	lpAnimation = new Animation();
	lpAnimation->Change("PLANET_SSJ", 50, true);
	speed = 200;
	elapsedTime = 0;
	angle = -PI / 2;
	lpFactory = new SSJFactory();	
	lpFactory->Init();

}

void Planet_SSJ::Update(float deltaTime)
{
	//lpImage = ImageManager::GetSingleton()->FindImage("PLANET_SSJ");

	Fire();

	lpAnimation->Update(deltaTime);
	elapsedTime += deltaTime;
}

void Planet_SSJ::Render(HDC hdc)
{
	Unit::Render(hdc);
}
