#pragma once
#include "Unit.h"

class Animation;
class SpaceShip_Red : public Unit
{
private:
	Animation* lpHitBoxAni;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};
