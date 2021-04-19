#pragma once
#include "BridgeShooter.h"
#include <vector>
#include "GameScene.h"

class HpGauge;
class Unit;
class Item;
class Image;
class InGameScene : public GameScene
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

	HpGauge* lpHpGauge;
	Image* lpHpGuageImage;

	int frame;
	float elapsedTime;
	

	float backgroundMover;
	bool isOnlyPlayer;
	bool isEnemyHitPlayer;
	bool isPlayerHitEnemy;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	void CheckCollision();
};

