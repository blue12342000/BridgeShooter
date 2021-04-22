#pragma once
#include "GameScene.h"

class Image;
class Ending : public GameScene 
{
private:
	float backgroundMover;
	Image* lpBackBuffer;
	Image* lpBackImage;
	Image* lpRetry;
	Animation* lpGhoust;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
};

