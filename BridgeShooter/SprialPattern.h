#pragma once
#include "Pattern.h"
class SprialPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

