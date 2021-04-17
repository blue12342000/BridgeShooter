#pragma once
#include "Pattern.h"

//가장 기본적인 미사일의 이동
class HomingPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;


};
