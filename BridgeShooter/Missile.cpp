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

	collider.SetHitBox(pos, this->deltaMove.deltaPos);

	elapsedTime += deltaTime;
}

void Missile::Release()
{
}

void Missile::Render(HDC hdc)
{
	
	if (lpImage) lpImage->RotateRender(hdc, pos.x + deltaMove.deltaPos.x, pos.y + deltaMove.deltaPos.y, deltaMove.angle);
	if(isDebugMode)
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	
}

void Missile::Move(float deltaTime)
{
	if (lpPattern) deltaMove = lpPattern->Move(deltaTime, this);
}

void Missile::SetMissile(string ImageKey, POINTFLOAT pos, POINTFLOAT deltaPos, float angle, float speed, int size, float delayTime)
{
	this->isActive = true;
	this->elapsedTime = 0;
	this->delayTime = delayTime;
	this->lpImage = ImageManager::GetSingleton()->FindImage(ImageKey);
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	this->deltaMove = { 0, 0 };
	collider.SetHitBox(pos, { 0, 0 }, size, size);
	
	lpPattern = nullptr;
}

void Missile::SetMissile(string ImageKey, POINTFLOAT pos, float angle, float speed, int size, float delayTime)
{
	this->isActive = true;
	this->elapsedTime = 0;
	this->delayTime = delayTime;
	this->lpImage = ImageManager::GetSingleton()->FindImage(ImageKey);
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	this->deltaMove = { 0, 0 };
	collider.SetHitBox(pos, { 0, 0 }, size, size);

	lpPattern = nullptr;
}
