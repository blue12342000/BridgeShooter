#pragma once
#include "Pattern.h"
class CircleMovePattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

