#pragma once
#include "Pattern.h"

//���� �⺻���� �̻����� �̵�
class RainPattern : public Pattern
{
private:

public:
	void Move(float deltaTime, GameObject* lpObject) override;
};
