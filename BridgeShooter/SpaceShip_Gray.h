#pragma once
#include "Unit.h"

class SpaceShip_Gray : public Unit
{
private:
	Animation* lpHitBoxAni;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};

