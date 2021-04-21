#include "Unit.h"
#include "Factory.h"
#include "Image.h"
#include "BridgeShooter.h"
#include "Animation.h"
#include "Pattern.h"

void Unit::Init()
{
	force.x = 0;
	force.y = 0;
	elapsedTime = 0;
	lpAnimation = nullptr;
	lpFactory = nullptr;
	lpPattern = nullptr;
}

void Unit::Update(float deltaTime)
{
	if (!lpPattern)
	{
		if (force.x > FLT_EPSILON || force.x < -FLT_EPSILON
			|| force.y > FLT_EPSILON || force.y < -FLT_EPSILON)
		{
			float dir = atan2(force.y, force.x);
			if (isInertia)
			{
				pos.x += cos(dir) * transform.speed * abs(force.x) / 10 * deltaTime;
				pos.y += sin(dir) * transform.speed * abs(force.y) / 10 * deltaTime;
			}
			else
			{
				pos.x += cos(dir) * transform.speed * deltaTime;
				pos.y += sin(dir) * transform.speed * deltaTime;
			}
		}
	}
	else
	{
		lpPattern->Move(deltaTime, this);
	}

	collider.SetHitBox(pos);
	if (lpFactory) lpFactory->Update(deltaTime);
	if (lpAnimation) lpAnimation->Update(deltaTime);
	if (isInertia)
	{
		if (force.x > FLT_EPSILON)
		{
			force.x -= 10 * deltaTime;;
			if (force.x < FLT_EPSILON) force.x = 0;
		}
		else if (force.x < FLT_EPSILON)
		{
			force.x += 10 * deltaTime;;
			if (force.x > FLT_EPSILON) force.x = 0;
		}
		if (force.y > FLT_EPSILON)
		{
			force.y -= 10 * deltaTime;;
			if (force.y < FLT_EPSILON) force.y = 0;
		}
		else if (force.y < FLT_EPSILON)
		{
			force.y += 10 * deltaTime;;
			if (force.y > FLT_EPSILON) force.y = 0;
		}
	}
	else
	{
		force.x = 0;
		force.y = 0;
	}
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

void Unit::Translate(POINTFLOAT force)
{
	if (force.x > FLT_EPSILON || force.x < -FLT_EPSILON
		|| force.y > FLT_EPSILON || force.y < -FLT_EPSILON)
	{
		this->force.x += force.x;
		this->force.y += force.y;
	
		if (abs(this->force.x) > 10) this->force.x = this->force.x / abs(this->force.x) * 10;
		if (abs(this->force.y) > 10) this->force.y = this->force.y / abs(this->force.y) * 10;
	}
}

void Unit::ChangeFactoryLine(int delta)
{
	SetFactoryLine(factoryLine + delta);
}

void Unit::ResetTimer()
{
	elapsedTime = 0;
	if (lpFactory) lpFactory->ResetTimer();
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

void Unit::SetFactoryLine(int factoryLine)
{
	if (lpFactory)
	{
		this->factoryLine = lpFactory->SetCreateLine(factoryLine);
	}
}
