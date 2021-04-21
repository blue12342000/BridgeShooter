#pragma once
#include "GameObject.h"

enum class ITEM_TYPE
{
	POWER_UP,	//À¯´ÖÀÇ »ý¼º¶óÀÎ ¹Ù²Þ
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
	
	inline void GetItemType(ITEM_TYPE type) { this->type = type; }

	void Move(float deltaTime);
};

