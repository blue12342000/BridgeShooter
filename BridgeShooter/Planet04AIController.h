#pragma once
#include "AIController.h"

class Planet04AIcontroller : public AIController
{
private:
	enum class USE_PATTERN
	{
		BASIC,
		RAIN,
		NONE
	};

	enum class UNIT_STATE
	{
		IDLE,
		MOVE,
		MOVE_ING,
		MOVE_PATTERN,
		PATTERN_ATTACK,
		ATTACK,
		RETURN,
		NONE
	};

private:
	UNIT_STATE state;
	USE_PATTERN currentPattern;

private:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void SetUnit(Unit* lpUnit);
};

