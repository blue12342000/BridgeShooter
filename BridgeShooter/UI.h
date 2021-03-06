#pragma once
#include "GameObject.h"

class UI : public GameEvent
{
public:
	UI() {}
	virtual ~UI() {}

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Release() = 0;
	virtual void Render(HDC hdc) = 0;
};

