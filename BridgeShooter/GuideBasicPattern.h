#pragma once
#include "Pattern.h"
class GuideBasicPattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};

