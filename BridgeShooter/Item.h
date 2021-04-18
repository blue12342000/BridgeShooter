#pragma once
#include "GameObject.h"


enum class ITEM_TYPE
{
	POWER_UP,
	BOMB,
	HP_POTION,
	SLOW_MOTION,
	TIME_STOP,
	NONE
};


class Image;
class Item : public GameObject
{
private:
	POINTFLOAT pos;
	int frame;
	float elapsedTime;

	float motionTimer;
	float motionSpeed;

public:
	ITEM_TYPE type;
	Image* lpImage;

public:
	void Init() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
};

