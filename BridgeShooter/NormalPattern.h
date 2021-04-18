#pragma once
#include "Pattern.h"
class NormalPattern :public Pattern
{
public: 
	virtual MoveInfo Move(float deltaTime, GameObject* lpObject);

};

