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
	pos.x += cosf(angle) * speed * deltaTime;
	pos.y += sinf(angle) * speed * deltaTime;
}

void Missile::Release()
{
}

void Missile::Render(HDC hdc)
{
	lpImage->Render(hdc, pos.x, pos.y, frame, U_IA_CENTER);
}

void Missile::Move(float deltaTime)
{
}
