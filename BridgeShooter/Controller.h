#pragma once
#include "GameObject.h"
#include <functional>

enum class INPUT_TYPE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ATTACK,
	NONE
};

class Unit;
class Controller : public GameEvent
{
private:
	struct UnitEvent
	{
		int key;
		function<void()> lpCmd;
	};

private:
	Unit* lpUnit;
	map<INPUT_TYPE, UnitEvent> mKeyMap;

public:
	void Init() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

	void SetController(Unit* lpUnit);
};

