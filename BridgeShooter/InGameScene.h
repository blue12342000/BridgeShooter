#pragma once
#include "BridgeShooter.h"
#include "GameScene.h"

class UIobject;
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
	vector<Controller*>vLpMobController;

	Unit* lpPlayer;
	Unit* lpPlanet04;
	Unit* lpPlanetSSJ;
	Unit* lpPlanetKMS;

	Unit* lpJinHwang;

	Item* lpItem;

	Controller* lpPlayerController;
	Controller* lpEnemyController;
	vector<Controller*> vLpEnemyController;


	Image* lpBackBuffer;
	Image* lpBackImage;
	Image* lpBackImage2;	

	UIobject* lpUIobject;

	STAGE_STATE currStage;
	STAGE_STATE nextStage;
	bool isBossAlive;
	bool isPlayerAlive;

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
