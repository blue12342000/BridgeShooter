#pragma once
#include <Windows.h>
#include "BridgeShooter.h"

class HpGauge
{
private:
	POINTFLOAT pos;

	RECT playerHpGauge;
	RECT enemyHpGauge;

	float size1;
	float size2;

	bool isPlayerAlive;
	bool isEnemyAlive;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void HpBarData();

	void SetHpBar1(RECT hpBar1) { this->playerHpGauge = playerHpGauge; }
	void SetHpBar2(RECT hpBar2) { this->enemyHpGauge = enemyHpGauge; }
	void SetSize1(int size1) { this->size1 = size1; }
	void SetSize2(int size2) { this->size2 = size2; }
	void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline POINTFLOAT GetPos() { return this->pos; }

	inline float GetSize1() { return this->size1; }
	inline float GetSize2() { return this->size2; }
	inline RECT GetHpBar1() { return this->playerHpGauge; }

};
