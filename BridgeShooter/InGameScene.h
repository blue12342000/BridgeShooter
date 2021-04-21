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
	enum class STAGE_STATE
	{
		LOADING,
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		NONE
	};

	enum class INGAME_STATE
	{
		NORMAL,
		SLOWTIME,
		NONE
	};

private:
	INGAME_STATE state;
	float slowTimer;
	float slowScale;
	STAGE_STATE currStage;
	STAGE_STATE nextStage;
	float elapsedTime;
	float backgroundMover;
	Image* lpBackBuffer;
	Image* lpBackImage;
	Image* lpBackImage2;
	Animation* lpLoadingCat;
	POINTFLOAT catPos;
	UIobject* lpUIobject;

	vector<Unit*> vEnemys;
	vector<Item*> vItems;
	vector<Controller*>vLpMobController;

	Controller* lpPlayerController;
	// ÂüÁ¶¿ë
	Controller* lpCurrentBossController;
	map<STAGE_STATE, Controller*> mLpBossController;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	void UnitCollision(UNIT_KIND attackerKind, Controller* target);
	bool ItemCollision(Unit* target, Item* item);

	void KillAlien(int indexNum);
	void CreateAlien(int indexNum);
};
