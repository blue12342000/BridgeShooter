#pragma once
#include "Unit.h"
class Planet_KMS :public Unit
{
public:
	virtual void Init() ;
	virtual void Update(float deltaTime) ;
	virtual void Release() ;
	virtual void Render(HDC hdc) ;
};

