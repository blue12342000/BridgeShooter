#pragma once
#include "Unit.h"

class Pattern;
class JinHwang : public Unit
{
private:
	float fireTimer;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};

