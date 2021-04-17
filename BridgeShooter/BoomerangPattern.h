#pragma once
#include "Pattern.h"
class BoomerangPattern :public Pattern
{
private:
	const float stopTime=6.0f;
	const float stopDuration = 1.0f;
public:
	virtual MoveInfo Move(float deltaTime, GameObject* lpObject);
};

