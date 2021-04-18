#include "Item.h"
#include "Image.h"

void Item::Init()
{
	lpImage = ImageManager::GetSingleton()->FindImage("Item_PowerUP");
	int frame;
	float elapsedTime =0.0f;

	float motionTimer = 0.0f;
	float motionSpeed = 12.0f;
	
	Image* lpImage;
}

void Item::Release()
{
}

void Item::Update(float deltaTime)
{
	lpImage = ImageManager::GetSingleton()->FindImage("Item_PowerUP");
	if (lpImage)
	{
		motionTimer += (deltaTime * motionSpeed);
		if (motionTimer > 1)
		{
			frame = (int)elapsedTime;
			frame %= lpImage->GetTotalFrame();
			motionTimer -= (int)motionTimer;

		}
	}
	elapsedTime += deltaTime;

	//collider.SetHitBox(pos, 100, 100);
}

void Item::Render(HDC hdc)
{
	if (lpImage) lpImage->Render(hdc, pos.x, pos.y, frame, U_IA_CENTER);
	if (isDebugMode)
	{
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	}
}
