#pragma once
#include "Pattern.h"

//���� �⺻���� �̻����� �̵�
class RainPattern : public Pattern
{
private:
	bool isFinished;
	bool isFired;
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;


};
