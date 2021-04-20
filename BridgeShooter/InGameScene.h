#pragma once
#include "BridgeShooter.h"
#include "GameScene.h"

class HpGauge;
class Unit;
class Item;
class Image;
class Controller;
class InGameScene : public GameScene
{
private:
	enum class STAGE_STATE
	{
		LOADING,
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		NONE
	};

private:
	vector<Unit*> vEnemys;
	vector<Item*> vItems;

	Unit* lpPlayer;
	Unit* lpPlanet04;
	Unit* lpPlanetSSJ;
	Unit* lpPlanetKMS;
	Unit* lpJinHwang;
	Unit* lpMob1;
		
	Item* lpItem;

	Controller* lpPlayerController;
	Controller* lpEnemyController;
	vector<Controller*> vLpMobController;

	Image* lpBackBuffer;
	Image* lpBackImage;	
	Image* lpBackImage2;	

	HpGauge* lpHpGauge;

	float elapsedTime;
	float backgroundMover;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	void CheckCollision( );
};

