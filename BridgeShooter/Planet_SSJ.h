#pragma once
#include "Unit.h"

class Planet_SSJ : public Unit
{
private:
	float fireTimer;
public:
	void Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render(HDC hdc) override;
};

