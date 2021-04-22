#pragma once
#include "UI.h"
#include "BridgeShooter.h"

class Item;
class Unit;
class Image;
class UIobject : public UI
{
private:
	Unit* lpPlayer;
	Unit* lpEnemy;

	RECT playerUIobject;
	RECT bossUIobject;

	Image* lpBossHpBar;
	Image* lpLifeStock[8];
	Image* lpMissile[6];
	Image* lpManual;
	Image* lpHp01;
	Image* lpHp02;
	Image* lpHp03;
	Image* lpHp04;

	float elapsedTime;

public:
	virtual void Init() ;
	virtual void Release() ;
	virtual void Update(float deltaTime) ;
	virtual void Render(HDC hdc) ;

	virtual void SetPlayer(Unit* lpPlayer) { this->lpPlayer = lpPlayer; }
	virtual void SetEnemy(Unit* lpEnemy) { this->lpEnemy = lpEnemy; }

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
