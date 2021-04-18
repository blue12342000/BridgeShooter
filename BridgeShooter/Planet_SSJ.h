#pragma once
#include "Unit.h"

class Planet_SSJ : public Unit
{

public:
	void Init() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
};

