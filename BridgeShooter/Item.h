#pragma once
#include "GameObject.h"

enum class ITEM_TYPE
{
	POWER_UP,	//¿Ø¥÷¿« ª˝º∫∂Û¿Œ πŸ≤ﬁ
	BOMB,
	HP_POTION,
	SPEED_UP,
	NONE
};

class Animation;
class Item : public GameObject
{
private:
	ITEM_TYPE type;
	Animation* lpAnimation;

public:
	void Init() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	
	inline ITEM_TYPE GetItemType() { return type; }

	void Move(float deltaTime);
};

