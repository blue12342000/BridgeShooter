#pragma once
#include "BridgeShooter.h"
#include <vector>
#include "GameScene.h"

class HpGauge;
class Unit;
class Item;
class Image;
class Controller;
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

	int frame;
	float elapsedTime;
	
	Controller* lpPlayerController;

	float backgroundMover;
	bool isOnlyPlayer;
	bool isEnemyHitPlayer;
	bool isPlayerHitEnemy;
	bool isPlayerHitItem;
	bool isItemAlive;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	void CheckCollision( );
};

