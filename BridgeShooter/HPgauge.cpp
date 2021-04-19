#include "HpGauge.h"
#include "InGameScene.h"
#include "Animation.h"
#include "Image.h"

void HpGauge::Init()
{
	//lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");
	playerMaxHp = 200;
	bossMaxHp = 500;
	isBossAlive = true;
	lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");
	hp =0;
	hpCount = 0;
	bombCount = 0;
	nowMissile = 0;
	fcukingManual = 0;
}

void HpGauge::Release()
{

}

void HpGauge::Update(float deltaTime)
{
	if (lpImage)
	{
		PlayerHpGaugeData(deltaTime);
		if (isBossAlive) BossHpGaugeData(deltaTime);
	}
}

void HpGauge::Render(HDC hdc)
{
	if (lpImage)
	{
		
		Rectangle(hdc, playerHpGauge.left, playerHpGauge.top, playerHpGauge.right, playerHpGauge.bottom);
	// 체력에 따라서 체력바 색상이 달라지게 하고싶다. 어떻게 할까
		if (isBossAlive)
		{
			Rectangle(hdc, bossHpGauge.left, bossHpGauge.top, bossHpGauge.right, bossHpGauge.bottom);
			lpImage->Render(hdc, WINSIZE_WIDTH/2, WINSIZE_HEIGHT/20, 0, U_IA_CENTER);
		}
	}
}

void HpGauge::PlayerHpGaugeData(float deltaTime)
{
	playerHpGauge = GetRectToCenter(playerMaxHp/2 + 50, 100, playerMaxHp, 18);

	//HP가 0되면 값 고정
	if (playerMaxHp <= 0)
	{
		playerMaxHp = 200;

	}
}

void HpGauge::BossHpGaugeData(float deltaTime)
{
	bossHpGauge = GetRectToCenter(bossMaxHp / 2 + 50, 50, bossMaxHp, 18);

	//HP가 0되면 값 고정
	if (bossMaxHp <= 0)
	{
		bossMaxHp = 500;
		isBossAlive = false;
	}
}

void HpGauge::HpCount(float deltaTime)
{

}

void HpGauge::BombCount(float deltaTime)
{
	
	bombCount++;
}

void HpGauge::NowMissile(float deltaTime)
{
}

void HpGauge::FcukingManual(float deltaTime)
{
}


