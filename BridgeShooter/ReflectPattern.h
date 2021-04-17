#pragma once
#include "Pattern.h"
class ReflectPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

