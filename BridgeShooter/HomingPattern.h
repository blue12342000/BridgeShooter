#pragma once
#include "Pattern.h"

//���� �⺻���� �̻����� �̵�
class HomingPattern : public Pattern
{
public:
	void Move(float deltaTime, GameObject* lpObject) override;


};
