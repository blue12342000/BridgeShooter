#pragma once
#include "Pattern.h"
class BoomerangPattern :public Pattern
{
private:
	const float stopTime=1.5f;
	const float stopDuration = 1.5f;
public:
    virtual MoveInfo Move(float deltaTime, GameObject* lpObject);
};