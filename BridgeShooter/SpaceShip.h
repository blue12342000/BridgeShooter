#pragma once
#include "Unit.h"

enum class INPUT_TYPE
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

class SpaceShip : public Unit
{
private:
	INPUT_TYPE input;
	float fireTimer;
	int power;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};
