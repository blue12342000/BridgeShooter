#pragma once
#include "Unit.h"

class SpaceShip : public Unit
{
private:
	float fireTimer;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;
};
