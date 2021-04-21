#pragma once
#include "GameScene.h"

class Image;
class Ending : public GameScene 
{
private:
	Image* lpEnding;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
};

