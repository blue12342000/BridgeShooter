#pragma once
#include "Unit.h"

class HpGauge;
class SpaceShip : public Unit
{
private:
	float fireTimer;
	int power;
	HpGauge* lpHpGauge;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};
