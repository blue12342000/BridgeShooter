#pragma once
#include "Controller.h"

enum class INPUT_COMMAND
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ATTACK,
	NONE
};

enum class INPUT_TYPE
{
	ONCE,
	STAY,
	NONE
};

class PlayerController : public Controller
{
private:
	struct UnitEvent
	{
		INPUT_TYPE type;
		int key;
		function<void()> lpCmd;
	};

private:
	map<INPUT_COMMAND, UnitEvent> mKeyMap;

private:
	void Init() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

	void SetController(Unit* lpUnit);
};

