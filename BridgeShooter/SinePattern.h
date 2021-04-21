#pragma once
#include "Pattern.h"

class SinePattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};

