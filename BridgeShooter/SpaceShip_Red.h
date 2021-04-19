#pragma once
#include "Unit.h"

enum class INPUT_TYPE3
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

class SpaceShip_Red : public Unit
{
private:
	INPUT_TYPE3 input;
	float fireTimer;
	int power;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};
