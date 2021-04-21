#pragma once
#include "Pattern.h"
class SpiralPattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};

