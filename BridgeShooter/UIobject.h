#pragma once
#include "UI.h"
#include "Unit.h"
#include "BridgeShooter.h"

class Item;
class SpaceShip;
class Unit;
class Image;
class UIobject : public Unit
{
private:
	Unit* lpPlayer;
	Unit* lpEnemy;

	RECT playerUIobject;
	RECT bossUIobject;

	Image* lpBossHpBar;
	Image* lpLifeStock;
	Image* lpBombCount;
	Image* lpMissile[4];
	Image* lpFcukingManual;

	int lifeAmount;
	int bombAmount;
	
	float playerMaxHp;
	float bossMaxHp;

	bool isMaxHp;

public:

	virtual void Init() ;
	virtual void Release() ;
	virtual void Update(float deltaTime) ;
	virtual void Render(HDC hdc) ;
	virtual void SetBossMaxHp();


	virtual void SetPlayer(Unit* lpPlayer) { this->lpPlayer = lpPlayer; }
	virtual void SetEnemy(Unit* lpEnemy) { this->lpEnemy = lpEnemy; }
	virtual void SetPlayerHpBar(RECT playerUIobject) { this->playerUIobject = playerUIobject; }
	virtual void SetBossHpBar(RECT enemyUIobject) { this->bossUIobject = enemyUIobject; }

	virtual void SetPlayerMaxHp(float playerMaxHp) { this->playerMaxHp = playerMaxHp; }
	virtual void SetBossMaxHp(float enemyMaxHp) { this->bossMaxHp = enemyMaxHp; }
	virtual void SetLifeAmount(int lifeAmount) { this->lifeAmount = lifeAmount; }
	virtual void SetBombAmount(int bombAmount) { this->bombAmount = bombAmount; }

	inline float GetPlayerMaxHp() { return this->playerMaxHp; }
	inline float GetBossMaxHp() { return this->bossMaxHp; }
	inline int GetBombAmount() { return this->bombAmount; }
	inline int GetLifeAmount() { return this->lifeAmount; }

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
