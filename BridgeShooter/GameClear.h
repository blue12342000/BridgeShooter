#pragma once
#include "GameScene.h"

class Unit;
class Controller;
class GameClear : public GameScene
{
private:
	Unit* lpCredit;
	Image* lpBackImage;
	Image* lpBackBuffer;

	Controller* lpPlayerController;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
};

