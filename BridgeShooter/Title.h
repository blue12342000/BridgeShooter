#pragma once
#include "GameScene.h"

class Image;
class Title : public GameScene
{
private:
	Image* lpBackBuffer;
	Image* lpTitle;
	Image* lpPressKey;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);

};

