#pragma once
#include "GameObject.h"

enum class ITEM_TYPE
{
	POWER_UP,
	HP_POTION,
	SLOW_MOTION,
	TIME_STOP,
	NONE
};

class Image;
class Item : public GameObject
{
private:
	int frame;
	float elapsedTime;

public:
	ITEM_TYPE type;
	Image* lpImage;

public:
	void Init() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
};

