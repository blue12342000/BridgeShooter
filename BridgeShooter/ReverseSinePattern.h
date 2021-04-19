#pragma once
#include "Pattern.h"

class ReverseSinePattern : public Pattern
{
private:

public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};

