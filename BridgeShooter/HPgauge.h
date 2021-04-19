#pragma once
#include "UI.h"
#include "BridgeShooter.h"

class Image;
class HpGauge : public UI
{
private:
	//POINTFLOAT pos;

	RECT playerHpGauge;
	RECT bossHpGauge;

	float playerMaxHp;
	float bossMaxHp;

	Image* lpImage;

	bool isBossAlive;

	int hp;
	int hpCount;
	int bombCount;
	int nowMissile;
	int fcukingManual;

public:

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;


	void PlayerHpGaugeData(float deltaTime);
	//void EnemyHpGaugeData(float deltaTime);
	void BossHpGaugeData(float deltaTime);

	void HpCount(float deltaTime);
	void BombCount(float deltaTime);
	void NowMissile(float deltaTime);
	void FcukingManual(float deltaTime);




	void SetPlayerHpGauge(RECT playerHpGauge) { this->playerHpGauge = playerHpGauge; }
	void SetbossHpGauge(RECT enemyHpGauge) { this->bossHpGauge = enemyHpGauge; }

	void SetPlayerMaxHp(int playerMaxHp) { this->playerMaxHp = playerMaxHp; }
	void SetbossMaxHp(int enemyMaxHp) { this->bossMaxHp = enemyMaxHp; }
	//void SetPos(POINTFLOAT pos) { this->pos = pos; }

	//inline POINTFLOAT GetPos() { return this->pos; }

	inline float GetPlayerMaxHp() { return this->playerMaxHp; }
	inline float GetbossMaxHp() { return this->bossMaxHp; }
	inline RECT GetPlayerHpGauge() { return this->playerHpGauge; }
	inline RECT GetbossHpGauge() { return this->bossHpGauge; }


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
