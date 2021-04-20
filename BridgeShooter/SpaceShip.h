#pragma once
#include "Unit.h"

class UIobject;
class SpaceShip : public Unit
{
private:
	float fireTimer;
	int power;
	UIobject* lpUIobject;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};
