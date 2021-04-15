#pragma once
#include "BridgeShooter.h"

class MainGame
{
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

