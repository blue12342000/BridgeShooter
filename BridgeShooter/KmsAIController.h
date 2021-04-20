#pragma once
#include "AIController.h"
class Pattern;
class KmsAIController :public AIController
{
protected:
	Pattern* lpPattern;
	int prevNum;
public:
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update(float deltaTime)override;
	virtual void Render(HDC hdc)override;
};

