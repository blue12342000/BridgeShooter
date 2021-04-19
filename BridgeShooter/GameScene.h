#pragma once
#include "BridgeShooter.h"

class GameScene
{
public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc) = 0;
};