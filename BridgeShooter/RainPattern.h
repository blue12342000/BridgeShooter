#pragma once
#include "Pattern.h"

//가장 기본적인 미사일의 이동
class RainPattern : public Pattern
{
private:
	bool isFinished;
	bool isFired;
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;


};
