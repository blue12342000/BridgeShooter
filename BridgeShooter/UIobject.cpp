#include "InGameScene.h"
#include "UIobject.h"
#include "Image.h"
#include "Unit.h""
#include "PlayerController.h"
#include "SpaceShip.h"

#include "Planet_SSJ.h"
#include "Planet04.h"
#include "JinHwang.h"
#include "Planet_KMS.h"
#include "Item.h"
#include "Missile.h"
#include "UIobject.h"
#include "GameScene.h"

void UIobject::Init()
{

	lpBossHpBar		= ImageManager::GetSingleton()->FindImage("BossHpGauge");
	lpBombCount		= ImageManager::GetSingleton()->FindImage("BombCount");
	lpFcukingManual = ImageManager::GetSingleton()->FindImage("Manual");
	lpLifeStock		= ImageManager::GetSingleton()->FindImage("HpCount");
	lpMissile[0]	= ImageManager::GetSingleton()->FindImage("NowMissile_1");
	lpMissile[1]	= ImageManager::GetSingleton()->FindImage("NowMissile_2");
	lpMissile[2]	= ImageManager::GetSingleton()->FindImage("NowMissile_3");
	lpMissile[3]	= ImageManager::GetSingleton()->FindImage("NowMissile_4");
	lpMissile[4]	= ImageManager::GetSingleton()->FindImage("NowMissile_MAXXX");
	lpMissile[5]	= ImageManager::GetSingleton()->FindImage("NowMissile_LVMAXXX");

	isMaxHp = true;
	
	playerMaxHp = 0; 
	bossMaxHp = 0;

	bombAmount = DataManager::GetSingleton()->GetBombAmount();
	lifeAmount = DataManager::GetSingleton()->GetLifeAmount();
}

void UIobject::Release()
{
}

void UIobject::Update(float deltaTime)
{
}


void UIobject::Render(HDC hdc)
{	
	//�ִ밪 ����.
	SetBossMaxHp();
	
	playerUIobject = GetRectToCenter(lpPlayer->GetHp() / 2 + 50, 80, lpPlayer->GetHp(), 18);
	Rectangle(hdc, playerUIobject.left, playerUIobject.top, playerUIobject.right, playerUIobject.bottom);
	// ü�¿� ���� ü�¹� ������ �޶����� �ϰ�ʹ�. ��� �ұ�
	bossUIobject = GetRectToCenter(lpEnemy->GetHp() / 2 + 50, 50, lpEnemy->GetHp(), 18);
	Rectangle(hdc, bossUIobject.left, bossUIobject.top, bossUIobject.right, bossUIobject.bottom);
	lpBossHpBar->Render(hdc, WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 20, 0, U_IA_CENTER);
	//��
	for (int i = 0; i < bombAmount; i++)
		lpBombCount->Render(hdc, 30+30* i, WINSIZE_HEIGHT / 8 + 50, 0, U_IA_CENTER);
	//��� . ������ ����
	for (int i = 0; i < lifeAmount; i++)
		lpLifeStock->Render(hdc, 30 + 30 * i, WINSIZE_HEIGHT / 8 + 15, 0, U_IA_CENTER);
	//ź����
	if (lpPlayer)
		lpMissile[lpPlayer->GetFactoryLine()]->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 70, 0, U_IA_CENTER);
	//�޴���
	lpFcukingManual->Render(hdc, WINSIZE_WIDTH -80, WINSIZE_HEIGHT / 2, 0, U_IA_CENTER);
}

//�ִ�ġ �����ϴ� �Լ�
void UIobject::SetBossMaxHp()
{
	if (isMaxHp)
	{
		SetPlayerMaxHp(lpPlayer->GetHp());
		SetBossMaxHp(lpEnemy->GetHp());
		isMaxHp = false;
	}
}