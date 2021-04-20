#include "Missile.h"
#include "Pattern.h"
#include "Animation.h"

void Missile::Init()
{
	lpAnimation = new Animation();
	elapsedTime = 0;

}

void Missile::Update(float deltaTime)
{
	Move(deltaTime);

	lpAnimation->Update(deltaTime);
	collider.SetHitBox(pos, this->deltaMove.deltaPos);
	elapsedTime += deltaTime;
}

void Missile::Release()
{
}

void Missile::Render(HDC hdc)
{
	
	if (lpAnimation) lpAnimation->Render(hdc, pos.x + deltaMove.deltaPos.x, pos.y + deltaMove.deltaPos.y, deltaMove.angle);
	if(isDebugMode)
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	
}

void Missile::Move(float deltaTime)
{
	if (lpPattern) deltaMove = lpPattern->Move(deltaTime, this);
}

void Missile::SetMissile(string ImageKey, POINTFLOAT pos, float angle, float speed, int size, float delayTime)
{
	this->elapsedTime = 0;
	this->delayTime = delayTime;
	this->lpAnimation->Change(ImageKey, 10, true, true);
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	this->deltaMove = { 0, 0 };
	collider.SetHitBox(pos, { 0, 0 }, size, size);

	lpPattern = nullptr;
}
