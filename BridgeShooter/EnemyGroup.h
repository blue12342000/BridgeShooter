#pragma once
#include "Unit.h"
class Pattern;
class EnemyGroup :public Unit
{
private:
	Pattern *lpPattern;
private:
	float moveAngle;
	float shootAngle;
public:
	virtual void Init() override;
	virtual void Update(float deltaTime)override;
	virtual void Release();
	virtual void Render(HDC hdc);
};

