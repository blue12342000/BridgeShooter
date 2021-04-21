#pragma once
#include "AIController.h"
class Pattern;
class KmsAIController :public AIController
{
protected:
	enum class USE_PATTERN
	{
		REFLECT,
		NONE
	};
	enum class UNIT_STATE
	{
		IDLE,
		MOVE,
		PATTERN_ATTACK,
		ATTACK,
		UPGRADE,
		RETURN,
		NONE
	};
protected:
	UNIT_STATE state;
	USE_PATTERN currentPattern;
	int prevNum;
public:
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update(float deltaTime)override;
	virtual void Render(HDC hdc)override;
};

