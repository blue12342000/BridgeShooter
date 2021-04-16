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
	Image* lpBackImage;		//¹è°æ
	int frame;
	float elapsedTime;
public:
	HRESULT Init();
	void Release();
	void Update(float delltaTime);
	void Render(HDC hdc);
};

