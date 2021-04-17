#pragma once
#include "Pattern.h"
class BoomerangPattern :public Pattern
{
private:
	bool isMove;
public:
	virtual MoveInfo Move(float deltaTime, GameObject* lpObject);
};

