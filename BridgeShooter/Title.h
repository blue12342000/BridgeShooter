#pragma once
#include "GameScene.h"

class Image;
class Animation;
class Title : public GameScene
{
private:
	Image* lpBackBuffer;
	Image* lpTitle;
	Image* lpPressKey;
	Animation* lpMovingCat;
	POINTFLOAT catPos;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);

};

