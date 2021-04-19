#include "UI.h"
#include "Factory.h"
#include "Image.h"
#include "BridgeShooter.h"
#include "Animation.h"

void UI::Init()
{
	elapsedTime = 0;
	lpAnimation = nullptr;
}
void UI::Update(float deltaTime)
{
	elapsedTime += deltaTime;
}
void UI::Release()
{
	if (lpAnimation)
	{
		delete lpAnimation;
	}
}
void UI::Render(HDC hdc)
{
	if (lpAnimation) lpAnimation->Render(hdc, pos.x, pos.y);
}
