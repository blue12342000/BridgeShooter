#pragma once
#include "Pattern.h"
class CircleMovePattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};

