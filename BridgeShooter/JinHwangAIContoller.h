#pragma once
#include "AIController.h"

class JinHwangAIContoller : public AIController
{
private:
	enum class UNIT_STATE
	{
		IDLE,
		MOVE,
		MOVE_ING,
		MOVE_PATTERN,
		MOVE_PATTERN_ING,
		PATTERN_ATTACK,
		ATTACK,
		UPGRADE,
		RETURN,
		NONE
	};

private:
	UNIT_STATE state;
	int moveCount;

private:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void SetUnit(Unit* lpUnit);
};

