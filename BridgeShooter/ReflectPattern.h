#pragma once
#include "Pattern.h"
class ReflectPattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};

