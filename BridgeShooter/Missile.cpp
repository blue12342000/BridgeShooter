#include "Missile.h"
#include "Pattern.h"
#include "Image.h"

void Missile::Init()
{
	lpImage = nullptr;
	isActive = false;
}

void Missile::Update(float deltaTime)
{
	Move(deltaTime);
	elapsedTime += deltaTime;
}

void Missile::Release()
{
}

void Missile::Render(HDC hdc)
{
	lpImage->Render(hdc, pos.x + deltaMove.deltaPos.x, pos.y + deltaMove.deltaPos.y, frame, U_IA_CENTER);
}

void Missile::Move(float deltaTime)
{
	if (lpPattern) deltaMove = lpPattern->Move(deltaTime, this);
}
