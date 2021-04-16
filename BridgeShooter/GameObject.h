#pragma once
#include "BridgeShooter.h"

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void Release() {}
	virtual void Render(HDC hdc) {}
};