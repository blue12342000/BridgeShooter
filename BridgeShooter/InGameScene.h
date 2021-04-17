#pragma once
#include "BridgeShooter.h"
#include <vector>

class Unit;
class Item;
class Image;
class InGameScene
{
private:
	vector<Unit*> vEnemys;
	vector<Item*> vItems;
	Unit* lpPlayer;
	Unit* lpPlanet;

	Image* lpBackBuffer;
	Image* lpBackImage;		//¹è°æ
	int frame;
	float elapsedTime;
	Unit* lpPlanetSSJ;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
};

