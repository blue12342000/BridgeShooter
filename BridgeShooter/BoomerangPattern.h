#pragma once
#include "Pattern.h"
class BoomerangPattern :public Pattern
{
public:
	virtual void Move(float deltaTime, GameObject* lpObject);
};

