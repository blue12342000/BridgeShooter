#include "UI.h"
#include "Factory.h"
#include "Image.h"
#include "BridgeShooter.h"
#include "Animation.h"

void UI::Init()
{
	lpAnimation = nullptr;
}
void UI::Update(float deltaTime)
{
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
	//if (lpAnimation) lpAnimation->Render(hdc, pos.x, pos.y);
}
