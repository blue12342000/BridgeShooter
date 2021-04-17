#include "Unit.h"
#include "Factory.h"
#include "Image.h"

void Unit::Init()
{
	elapsedTime = 0;
	frame = 0;
	lpImage = nullptr;
	lpFactory = nullptr;
}
void Unit::Update(float deltaTime)
{
	elapsedTime += deltaTime;
}
void Unit::Release()
{
}
void Unit::Render(HDC hdc)
{
	if (lpImage) lpImage->Render(hdc, pos.x, pos.y, frame, U_IA_CENTER);
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
