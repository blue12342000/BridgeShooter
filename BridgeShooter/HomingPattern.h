#pragma once
#include "Pattern.h"

//���� �⺻���� �̻����� �̵�
class HomingPattern : public Pattern
{
public:
	MoveInfo Move(float deltaTime, GameObject* lpObject) override;


};
