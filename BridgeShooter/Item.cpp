#include "Item.h"
#include "Image.h"

void Item::Init()
{
	lpImage = ImageManager::GetSingleton()->FindImage("Item");
}

void Item::Release()
{
}

void Item::Update(float deltaTime)
{
	if (!lpImage) return;

	elapsedTime += deltaTime;
	frame = (int)elapsedTime;
	frame %= lpImage->GetTotalFrame();
}

void Item::Render(HDC hdc)
{
	if (lpImage) lpImage->Render(hdc);
}