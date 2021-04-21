#pragma once
#include "Pattern.h"

class BasicPattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};

