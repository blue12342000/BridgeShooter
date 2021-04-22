#pragma once
#include "GameObject.h"

enum class ITEM_TYPE
{
	POWER_UP,
	BOMB,
	HP_POTION,
	SPEED_UP,
	NONE
};

class Animation;
class Item : public GameObject
{
private:
	bool isActive;
	ITEM_TYPE type;
	Animation* lpAnimation;
	float changeTimer;

public:
	void Init() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	
	void Move(float deltaTime);

	inline ITEM_TYPE GetItemType() { return type; }
	inline bool IsActive() { return isActive; }
	inline void SetIsActive(bool isActive) { this->isActive = isActive; }
};

