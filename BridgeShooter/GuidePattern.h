#pragma once
#include "Pattern.h"

class GuidePattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};