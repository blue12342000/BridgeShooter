#pragma once
#include "GameObject.h"
#include <functional>

class Unit;
class Controller : public GameEvent
{
protected:
	bool isReady;
	Unit* lpUnit;

public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void SetUnit(Unit* lpUnit) = 0;


	inline Unit* GetUnit() { return this->lpUnit; }
	inline bool IsReady() { return isReady; }
	inline void SetIsReady(bool isReady) { this->isReady = isReady; }
};

