#pragma once
#include "Unit.h"
class AlienRed :public Unit
{
private:
	Pattern* lpPattern;
private:
	float moveAngle;
	float shootAngle;
	int	  shootDuration;
public:
	virtual void Init() override;
	virtual void Update(float deltaTime)override;
	virtual void Release();
	virtual void Render(HDC hdc);
};

