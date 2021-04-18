#include "Missile.h"
#include "Pattern.h"
#include "Image.h"

void Missile::Init()
{
	lpImage = nullptr;
	isActive = false;
	elapsedTime = 0;

}

void Missile::Update(float deltaTime)
{
	Move(deltaTime);

	collider.SetHitBox(pos);

	elapsedTime += deltaTime;
}

void Missile::Release()
{
}

void Missile::Render(HDC hdc)
{
	if (lpImage) lpImage->RotateRender(hdc, pos.x + deltaMove.deltaPos.x, pos.y + deltaMove.deltaPos.y, deltaMove.angle);
}

void Missile::Move(float deltaTime)
{
	if (lpPattern) deltaMove = lpPattern->Move(deltaTime, this);
}

void Missile::SetMissile(string ImageKey, POINTFLOAT pos, float angle, float speed, int size, float delayTime)
{
	this->isActive = true;
	this->elapsedTime = 0;
	this->delayTime = delayTime;
	this->lpImage = ImageManager::GetSingleton()->FindImage("ImageKey");
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	collider.SetHitBox(pos, size, size);
	
	lpPattern = nullptr;
}
