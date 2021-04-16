#pragma once
#include "Pattern.h"

//가장 기본적인 미사일의 이동
class BasicPattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;


};

