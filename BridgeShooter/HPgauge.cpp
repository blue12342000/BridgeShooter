#include "HpGauge.h"
#include "InGameScene.h"
#include "Animation.h"
#include "Image.h"

void HpGauge::Init()
{
	//lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");
	playerMaxHp = 200;
	bossMaxHp = 500;
	
	isBossAlive=true;
	isBombUsed = false;
	isBombLeft = true;
	isHpLeft = true;
	isNowMissile1 = true;
	isPushedManualButton = true;

	lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");

	for (int i = 0; i < 3; i++)
	{
		lpHpCount[i] = ImageManager::GetSingleton()->FindImage("HpCount");
		lpBombCount[i] = ImageManager::GetSingleton()->FindImage("BombCount");
	}
	lpNowMissile = ImageManager::GetSingleton()->FindImage("NowMissile_1");
	lpFcukingManual = ImageManager::GetSingleton()->FindImage("Manual");

	hp =0;
	hpCount = 3;
	bombCount = 3;
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
		if (isBombUsed)
		{
			BombCount(deltaTime);
		}
		//�̹��� ��� �ϳ� ����
		if (isNowMissile1)
		{
			//�̹��� ���.
		}
	}
}

void HpGauge::Render(HDC hdc)
{
	if (lpImage)
	{

		Rectangle(hdc, playerHpGauge.left, playerHpGauge.top, playerHpGauge.right, playerHpGauge.bottom);
		// ü�¿� ���� ü�¹� ������ �޶����� �ϰ�ʹ�. ��� �ұ�
		if (isBossAlive)
		{
			Rectangle(hdc, bossHpGauge.left, bossHpGauge.top, bossHpGauge.right, bossHpGauge.bottom);
			lpImage->Render(hdc, WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 20, 0, U_IA_CENTER);
		}
		if (isBombLeft)
		{
			for (int i = 0; i < bombCount; i++)
			{
				lpBombCount[i]->Render(hdc, WINSIZE_WIDTH / 7 + 50*i, WINSIZE_HEIGHT / 8 + 100, 0, U_IA_CENTER);
			}
		}
		if (isHpLeft)
		{
			for (int i = 0; i < hpCount; i++)
			{
				lpHpCount[i]->Render(hdc, WINSIZE_WIDTH / 7 + 50 *i, WINSIZE_HEIGHT / 8 + 50, 0, U_IA_CENTER);
			}
		}
		if (isNowMissile1)
		{
			lpNowMissile->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 100, 0, U_IA_CENTER);
		}
		if (isPushedManualButton)
		{
			lpFcukingManual->Render(hdc, WINSIZE_WIDTH / 10, WINSIZE_HEIGHT / 2, 0, U_IA_CENTER);
		}
	}
}

void HpGauge::PlayerHpGaugeData(float deltaTime)
{
	playerHpGauge = GetRectToCenter(playerMaxHp/2 + 50, 100, playerMaxHp, 18);

	//HP�� 0�Ǹ� �� ����
	if (playerMaxHp <= 0)
	{
		playerMaxHp = 200;
		hpCount--;
		if (hpCount < 0)
		{
			hpCount = 0;
			playerMaxHp = 200;
		}
	}
}

void HpGauge::BossHpGaugeData(float deltaTime)
{
	bossHpGauge = GetRectToCenter(bossMaxHp / 2 + 50, 50, bossMaxHp, 18);

	//HP�� 0�Ǹ� �� ����
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
	bombCount--;
	isBombUsed = false;
	if (bombCount < 0)
		bombCount = 0;
}

void HpGauge::IsBombUsed(float deltaTime)
{
	isBombUsed = true;
}


void HpGauge::NowMissile(float deltaTime)
{
}

void HpGauge::FcukingManual(float deltaTime)
{
}


