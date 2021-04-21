#include "Item.h"
#include "Animation.h"
#include "Pattern.h"
#include "ReflectPattern.h"

void Item::Init()
{
    isActive = false;
	angle = (rand() % 360) / 180.0f * PI;
	transform.speed = 400;
	elapsedTime = 0.0f;
    type = (ITEM_TYPE)(rand() % (int)ITEM_TYPE::NONE);
    lpPattern = new ReflectPattern();
    lpAnimation = new Animation();
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
    }
    collider.SetHitBox(pos, 60, 60);
    changeTimer = 3;
}

void Item::Release()
{
    delete lpAnimation;
    delete lpPattern;
}

void Item::Update(float deltaTime)
{
    if (!isActive) return;
    if (pos.x < WINSIZE_LEFT || pos.y < WINSIZE_TOP
        || pos.x > WINSIZE_RIGHT || pos.y > WINSIZE_BOTTOM)
    {
        isActive = false;
        return;
    }

    changeTimer -= deltaTime;
    if (changeTimer < 0)
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
        }
        changeTimer = 3;
    }
    
    Move(deltaTime);
    if (lpAnimation) lpAnimation->Update(deltaTime);
    collider.SetHitBox(pos);
    elapsedTime += deltaTime;
}

void Item::Render(HDC hdc)
{
    if (!isActive) return;
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