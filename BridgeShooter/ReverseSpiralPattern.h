#pragma once
#include "Pattern.h"

class ReverseSpiralPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

