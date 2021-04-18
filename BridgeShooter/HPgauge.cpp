#include "HpGauge.h"
#include "InGameScene.h"

HRESULT HpGauge::Init()
{
	pos.x = 0;
	pos.y = 0;

	isEnemyAlive = true;
	isPlayerAlive = false;

	size1 = 1000;
	size2 = 1000;

	return S_OK;
}

void HpGauge::Release()
{
}

void HpGauge::Update()
{
	HpBarData();
}

void HpGauge::Render(HDC hdc)
{
	Rectangle(hdc, playerHpGauge.left, playerHpGauge.top, playerHpGauge.right, playerHpGauge.bottom);
	Rectangle(hdc, enemyHpGauge.left, enemyHpGauge.top, enemyHpGauge.right, enemyHpGauge.bottom);
}

void HpGauge::HpBarData()
{
	//playerHpGauge = GetRectToCenter(pos.x + 294, pos.y + 42, size1 / 4, 50);
	//enemyHpGauge = GetRectToCenter(pos.x + 825, pos.y + 39, size2 / 4, 50);

	if (size1 <= 0)
	{
		size1 = 0;
	}
	if (size2 <= 0)
	{
		size2 = 0;
	}
}