#pragma once
#include "Pattern.h"
#include "GuideBasicPattern.h"

class BoomerangPattern :public Pattern
{
private:
	const float stopTime = 1.5f;
	const float stopDuration = 1.5f;
	GuideBasicPattern guideBasicPattern;

public:
    virtual void Move(float deltaTime, GameObject* lpObject);
};