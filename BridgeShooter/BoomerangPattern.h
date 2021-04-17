#pragma once
#include "Pattern.h"
class BoomerangPattern :public Pattern
{
private:
	bool isMove;
public:
	virtual void Move(float deltaTime, GameObject* lpObject);
};

