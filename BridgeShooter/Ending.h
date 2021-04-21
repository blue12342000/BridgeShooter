#pragma once
#include "GameScene.h"

class Ending : public GameScene 
{
public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
};

