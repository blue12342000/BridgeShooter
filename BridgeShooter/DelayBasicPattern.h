#pragma once
#include "Pattern.h"

class DelayBasicPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};


