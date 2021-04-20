#pragma once
#include "BridgeShooter.h"
#include "GameScene.h"

class HpGauge;
class Unit;
class Item;
class Image;
class Controller;
class Animation;
class InGameScene : public GameScene
{
private:
	enum STAGE_STATE
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

	Image* lpBackBuffer;
	Image* lpBackImage;
	Image* lpBackImage2;	

	HpGauge* lpHpGauge;

	STAGE_STATE currStage;
	STAGE_STATE nextStage;
	bool isBossAlive;

	Animation* lpLoadingCat;
	POINTFLOAT catPos;

	float elapsedTime;
	float backgroundMover;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	void CheckCollision();
};
