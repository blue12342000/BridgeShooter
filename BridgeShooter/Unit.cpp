#include "Unit.h"
#include "Factory.h"
#include "Image.h"
#include "BridgeShooter.h"
#include "Animation.h"

void Unit::Init()
{
	elapsedTime = 0;
	lpAnimation = nullptr;
	lpFactory = nullptr;
}

void Unit::Update(float deltaTime)
{
	if (force.x || force.y)
	{
		float dir = atan2(force.y, force.x);
		pos.x += cos(dir) * speed * deltaTime;
		pos.y += sin(dir) * speed * deltaTime;
	}

	collider.SetHitBox(pos);
	if (lpFactory) lpFactory->Update(deltaTime);
	if (lpAnimation) lpAnimation->Update(deltaTime);
	force.x = 0;
	force.y = 0;
	elapsedTime += deltaTime;
}

void Unit::Release()
{
	if (lpAnimation)
	{
		delete lpAnimation;
	}
	if (lpFactory)
	{
		lpFactory->Release();
		delete lpFactory;
	}
}

void Unit::Render(HDC hdc)
{
	if (lpAnimation) lpAnimation->Render(hdc, pos.x, pos.y);
	if (isDebugMode)
	{
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	}
}

void Unit::Fire(void)
{
	if (lpFactory) lpFactory->Fire(this);
}

void Unit::Translate(POINT force)
{
	if (force.x || force.y)
	{
		this->force.x += force.x;
		this->force.y += force.y;

		if (this->force.x) this->force.x /= abs(this->force.x);
		if (this->force.y) this->force.y /= abs(this->force.y);
	}
}

void Unit::SetFactory(Factory* lpFactory)
{
	if (this->lpFactory)
	{
		this->lpFactory->Release();
		delete this->lpFactory;
	}

	this->lpFactory = lpFactory;
	this->lpFactory->Init();
}
