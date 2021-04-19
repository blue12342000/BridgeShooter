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
	Unit* lpPlanet04;
	Unit* lpPlanetSSJ;
	Unit* lpPlanetKMS;

	Unit* lpJinHwang;

	Item* lpItem;		

	Image* lpBackBuffer;
	Image* lpBackImage;		
	Image* lpBackImage2;	
	int frame;
	float elapsedTime;
	

	float backgroundMover;
	bool isOnlyPlayer;
	bool isEnemyHitPlayer;
	bool isPlayerHitEnemy;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void CheckCollision();
};

