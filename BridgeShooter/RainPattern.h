#pragma once
#include "Pattern.h"

//���� �⺻���� �̻����� �̵�
class RainPattern : public Pattern
{
private:

public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;
};
