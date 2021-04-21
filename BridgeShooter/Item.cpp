#include "Item.h"
#include "Animation.h"
#include "Pattern.h"
#include "ReflectPattern.h"

void Item::Init()
{
	angle = PI / 4;
	transform.speed = 400;
	elapsedTime = 0.0f;
    type = (ITEM_TYPE)(rand() % (int)ITEM_TYPE::NONE);
    lpPattern = new ReflectPattern();
    lpAnimation = new Animation();
    lpAnimation->Change("Item_Bomb", 20, true);
    collider.SetHitBox(pos, 60, 60);
}

void Item::Release()
{
    delete lpAnimation;
    delete lpPattern;
}

void Item::Update(float deltaTime)
{
    if ((int)type != (int)(elapsedTime / 3))
    {
        type = (ITEM_TYPE)(((int)type + 1) % (int)ITEM_TYPE::NONE);
        switch (type)
        {
        case ITEM_TYPE::POWER_UP:
            lpAnimation->Change("Item_Power", 10, true);
            break;
        case ITEM_TYPE::BOMB:
            lpAnimation->Change("Item_Bomb", 10, true);
            break;
        case ITEM_TYPE::HP_POTION:
            lpAnimation->Change("Item_Health", 10, true);
            break;
        case ITEM_TYPE::SPEED_UP:
            lpAnimation->Change("Item_Speed", 10, true);
            break;
            break;
        }
    }
    
    Move(deltaTime);
    if (lpAnimation) lpAnimation->Update(deltaTime);
    collider.SetHitBox(pos);
    elapsedTime += deltaTime;
}

void Item::Render(HDC hdc)
{
	if (lpAnimation) lpAnimation->Render(hdc, pos.x, pos.y, angle);
	if (isDebugMode)
	{
		Ellipse(hdc, collider.hitBox.left, collider.hitBox.top, collider.hitBox.right, collider.hitBox.bottom);
	}
}

//ReflectPattern
void Item::Move(float deltaTime)
{
    if (lpPattern)
    {
        lpPattern->Move(deltaTime, this);
    }
}