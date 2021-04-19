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
	bossMaxHp = 100000;
	isBossAlive = true;
	lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");

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

		elapsedTime += deltaTime;
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
			lpImage->Render(hdc, pos.x, pos.y, 0, U_IA_CENTER);
		}
	}
}

void HpGauge::PlayerHpGaugeData(float deltaTime)
{
	playerHpGauge = GetRectToCenter(playerMaxHp/2 / 100 + 50, 100, playerMaxHp/100, 18);

	//HP�� 0�Ǹ� �� ����
	if (playerMaxHp <= 0)
	{
		playerMaxHp = 20000;
	}
}

void HpGauge::BossHpGaugeData(float deltaTime)
{
	bossHpGauge = GetRectToCenter(bossMaxHp / 2 / 200 + 50, 50, bossMaxHp / 200, 18);

	//HP�� 0�Ǹ� �� ����
	if (bossMaxHp <= 0)
	{
		bossMaxHp = 100000;
		isBossAlive = false;
	}
}


