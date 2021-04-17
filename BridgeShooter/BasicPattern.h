#pragma once
#include "Pattern.h"

class BasicPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

