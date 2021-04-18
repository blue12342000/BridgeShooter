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
void Unit::Fire(void)
{
	if (lpFactory) lpFactory->Fire(this);
}
