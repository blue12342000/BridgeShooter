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

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void SetController(Unit* lpUnit) final { this->lpUnit = lpUnit; };
};

