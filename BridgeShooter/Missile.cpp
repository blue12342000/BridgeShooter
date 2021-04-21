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
	collider.SetHitBox(pos);
	elapsedTime += deltaTime;
}

void Missile::Release()
{
}

void Missile::Render(HDC hdc)
{
	
	if (lpAnimation) lpAnimation->Render(hdc, pos.x, pos.y, angle);
	if(isDebugMode)
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	
}

void Missile::Move(float deltaTime)
{
	if (lpPattern) lpPattern->Move(deltaTime, this);
}

void Missile::SetMissile(string ImageKey, float angle, Transform transform, int size, float delayTime)
{
	this->lpAnimation->Change(ImageKey, 10, true, true);
	this->transform = transform;
	this->pos = transform.pos;
	this->angle = angle;
	this->delayTime = delayTime;
	collider.SetHitBox(transform.pos, size, size);
	lpPattern = nullptr;
}
