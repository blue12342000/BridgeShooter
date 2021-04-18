#pragma once
#include "Pattern.h"

class ReverseSinePattern : public Pattern
{
private:
	int scale = 10;

public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

