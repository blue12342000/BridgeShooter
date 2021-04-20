#pragma once
#include "UI.h"
#include "BridgeShooter.h"

class Item;
class SpaceShip;
class Unit;
class Image;
class Controller;
class UIobject : public UI
{
private:
	vector<Unit*> vEnemys;
	vector<Item*> vItems;
	Unit* lpPlayer;
	Unit* lpPlanet04;
	Unit* lpJinHwang;
	Unit* lpPlanetSSJ;
	Unit* lpPlanetKMS;
	Unit* lpEnemyGroup;
	Unit* lpSpaceShip;
	Unit* lpSpaceShip_Gray;
	Unit* lpSpaceShip_Red;
	


	Controller* lpPlayerController;
	Controller* lpEnemyController;

	RECT playerUIobject;
	RECT bossUIobject;

	float playerMaxHp;
	float bossMaxHp;

	Image* lpImage;
	Image* lpHpCount[3];
	Image* lpBombCount[3];
	Image* lpMissile[3];
	Image* lpFcukingManual;

	bool isBossAlive;
	bool isBombUsed;
	bool isBombLeft;
	bool isHpLeft;
	bool isNowMissile;
	bool isPushedManualButton;

	int hp;
	int hpCount;
	int bomb;
	int bombAmount;
	int fcukingManual;
	int index;
	int power;
	int createLine;


public:

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;


	void PlayerUIobjectData( );
	//void EnemyUIobjectData(float deltaTime);
	void BossUIobjectData( );
	void IndexData();

	void HpCount( );
	void BombCount( );
	void NowMissile( );
	void FcukingManual( );
	void IsBombUsed();
	void IndexControl(HDC hdc);


	void SetPlayerUIobject(RECT playerUIobject) { this->playerUIobject = playerUIobject; }
	void SetbossUIobject(RECT enemyUIobject) { this->bossUIobject = enemyUIobject; }

	void SetPlayerMaxHp(int playerMaxHp) { this->playerMaxHp = playerMaxHp; }
	void SetbossMaxHp(int enemyMaxHp) { this->bossMaxHp = enemyMaxHp; }
	void SetBombAmount(int bombAmount) { this->bombAmount = bombAmount; }
	void SetFactoryLine(int createLine) { this->createLine = createLine; }
	
	//void SetPos(POINTFLOAT pos) { this->pos = pos; }

	//inline POINTFLOAT GetPos() { return this->pos; }

	inline float GetPlayerMaxHp() { return this->playerMaxHp; }
	inline float GetbossMaxHp() { return this->bossMaxHp; }
	inline float GetBombAmount() { return this->bombAmount; }
	inline float GetFactoryLine(){ return this->createLine; }


	inline RECT GetPlayerUIobject() { return this->playerUIobject; }
	inline RECT GetbossUIobject() { return this->bossUIobject; }


	inline void RenderRectToCenter(HDC hdc, int x, int y, int width, int height)
	{
		Rectangle(hdc,
			x - (width / 2), y - (height / 2),
			x + (width / 2), y + (height / 2));
	}

	inline RECT GetRectToCenter(int posX, int posY, int width, int height)
	{
		RECT rc{ posX - (width / 2), posY - (height / 2), posX + (width / 2), posY + (height / 2) };
		return rc;
	}
};
