#pragma once
#include "Unit.h"
class AlienGreen :public Unit
{
public:
	virtual void Init() override;
	virtual void Update(float deltaTime)override;
	virtual void Release();
	virtual void Render(HDC hdc);
};

