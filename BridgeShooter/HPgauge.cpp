#include "HpGauge.h"
#include "InGameScene.h"
#include "Animation.h"
#include "Image.h"

void HpGauge::Init()
{
	pos.x = 0;
	pos.y = 0;
	//lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");
	playerMaxHp = 20000;
	bossMaxHp = 500000;
	isBossAlive = true;
}

void HpGauge::Update(float deltaTime)
{
	PlayerHpGaugeData(deltaTime);
	if (isBossAlive) BossHpGaugeData(deltaTime);

	elapsedTime += deltaTime;
}

void HpGauge::Render(HDC hdc)
{
	Rectangle(hdc, playerHpGauge.left, playerHpGauge.top, playerHpGauge.right, playerHpGauge.bottom);
	if(isBossAlive)
	Rectangle(hdc, bossHpGauge.left, bossHpGauge.top, bossHpGauge.right, bossHpGauge.bottom);
	UI::Render(hdc);
}

void HpGauge::PlayerHpGaugeData(float deltaTime)
{
	playerHpGauge = GetRectToCenter(playerMaxHp/2 / 100 + 50, 100, playerMaxHp/100, 18);

	//HP가 0되면 값 고정
	if (playerMaxHp <= 0)
	{
		playerMaxHp = 0;
	}
}

void HpGauge::BossHpGaugeData(float deltaTime)
{
	bossHpGauge = GetRectToCenter(bossMaxHp / 2 / 1000 + 50, 50, bossMaxHp / 1000, 18);

	//HP가 0되면 값 고정
	if (playerMaxHp <= 0)
	{
		playerMaxHp = 0;
		isBossAlive = false;
	}
}


