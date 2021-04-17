#pragma once
#include "Pattern.h"
class SpiralPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

