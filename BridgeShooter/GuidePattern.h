#pragma once
#include "Pattern.h"

class GuidePattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;
};