#pragma once
#include "Controller.h"

class Pattern;
class AIController : public Controller
{
protected:
	float elapsedTime;
	POINTFLOAT origin;
	vector<Pattern*> vLpPatterns;

public:

	virtual void Init() {};
	virtual void Release() {};
	virtual void Update(float deltaTime) {};
	virtual void Render(HDC hdc) {};

	virtual void SetUnit(Unit* lpUnit) = 0;
};

