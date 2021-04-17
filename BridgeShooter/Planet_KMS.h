#pragma once
#include "Unit.h"
class Planet_KMS :public Unit
{
private:
	float attack1Timer;
public:
	virtual void Init() ;
	virtual void Update(float deltaTime) ;
	virtual void Release() ;
	virtual void Render(HDC hdc) ;
};

