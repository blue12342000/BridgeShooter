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
	if (force.force > 0.000001f)
	{
		float dir = atan2(force.dir.y, force.dir.y);
		pos.x += cos(dir) * speed * deltaTime;
		pos.y += sin(dir) * speed * deltaTime;
	}

	collider.SetHitBox(pos);
	if (lpFactory) lpFactory->Update(deltaTime);
	if (lpAnimation) lpAnimation->Update(deltaTime);
	force.force = 0;
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

void Unit::Translate(Force force)
{
	//if (force.force > 0.0000001f)
	//{
	//	this->force.x += force.x;
	//	this->force.y += force.y;
	//
	//	if (this->force.x) this->force.x /= abs(this->force.x);
	//	if (this->force.y) this->force.y /= abs(this->force.y);
	//}
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
