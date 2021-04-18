#include "Item.h"
#include "Image.h"

void Item::Init()
{
	angle = PI/17;
	speed = 1000;
	lpImage = ImageManager::GetSingleton()->FindImage("Item_Bomb");
	elapsedTime = 0.0f;
	motionTimer = 0.0f;
	motionSpeed = 4;
    count = 0;
    delayTime = 0;
    isItemAlive = true;
}

void Item::Release()
{
}

void Item::Update(float deltaTime)
{
	Move(deltaTime);
    
    if (lpImage)    //이미지 호출이오면
    {
        ++count;
        motionTimer += (deltaTime * motionSpeed);
        if (motionTimer > 1)
        {
            frame += (int)motionTimer;
            frame %= lpImage->GetTotalFrame();
            motionTimer -= (int)motionTimer;
        }


        if (elapsedTime < 27.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Power");
        if (elapsedTime < 24.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Bomb");
        if (elapsedTime < 21.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Power");
        if (elapsedTime < 18.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Bomb");
        if (elapsedTime < 15.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Power");
        if (elapsedTime < 12.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Bomb");
        if (elapsedTime < 9.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Power");
        if (elapsedTime < 6.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Bomb");
        if (elapsedTime < 3.0f)
            lpImage = ImageManager::GetSingleton()->FindImage("Item_Power");
    }

	elapsedTime += deltaTime;

	collider.SetHitBox(pos, 50, 50);
}

void Item::Render(HDC hdc)
{
	if (lpImage) lpImage->Render(hdc, pos.x, pos.y, frame, U_IA_CENTER);
	if (isDebugMode)
	{
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	}
}

//ReflectPattern을 때려박아서 만듬
void Item::Move(float deltaTime)
{

    if (isItemAlive)
    {
        pos.x += cos(angle) * speed * deltaTime / 3;
        pos.y += sin(angle) * speed * deltaTime / 3;

        while (angle > PI * 2) angle -= PI * 2;
        while (angle < 0) angle += PI * 2;
        
        if (elapsedTime < 60)
        {
            if (pos.x < 0)
            {
                pos.x = 0;
                if (angle > PI)
                {
                    angle = PI * 3 - angle;
                }
                else
                {
                    angle = PI - angle;
                }
            }

            else if (pos.x > WINSIZE_WIDTH)
            {
                pos.x = WINSIZE_WIDTH;
                if (angle > PI)
                {
                    angle = 3 * PI - angle;
                }
                else
                {
                    angle = PI - angle;
                }
            }

            if (pos.y < 0)
            {
                pos.y = 0;
                angle = PI * 2 - angle;
            }
            else if (pos.y > WINSIZE_HEIGHT)
            {
                pos.y = WINSIZE_HEIGHT;
                if (angle > PI / 2)
                {
                    angle = PI * 2 - angle;
                }
                else
                    angle = -angle;
            }
        }
    }

}