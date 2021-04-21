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
	lpFcukingManual = ImageManager::GetSingleton()->FindImage("Manual");
	lpLifeStock		= ImageManager::GetSingleton()->FindImage("HpCount");
	lpMissile[0]	= ImageManager::GetSingleton()->FindImage("NowMissile_1");
	lpMissile[1]	= ImageManager::GetSingleton()->FindImage("NowMissile_2");
	lpMissile[2]	= ImageManager::GetSingleton()->FindImage("NowMissile_3");
	lpMissile[3]	= ImageManager::GetSingleton()->FindImage("NowMissile_LVMAXXX");
	//lpMissile[3]	= ImageManager::GetSingleton()->FindImage("NowMissile_4");
	lpMissile[4]	= ImageManager::GetSingleton()->FindImage("NowMissile_MAXXX");
	lpMissile[5]	= ImageManager::GetSingleton()->FindImage("NowMissile_LVMAXXX");
	lpHp01			= ImageManager::GetSingleton()->FindImage("hp_01");
	lpHp02			= ImageManager::GetSingleton()->FindImage("hp_02");
	lpHp03			= ImageManager::GetSingleton()->FindImage("hp_03");
	lpHp04			= ImageManager::GetSingleton()->FindImage("hp_04");

	isMaxHp = true;
	
	playerMaxHp = 0; 
	bossMaxHp = 0;

	
}

void UIobject::Release()
{
}

void UIobject::Update(float deltaTime)
{
}


void UIobject::Render(HDC hdc)
{	
	//최대값 저장.
	//SetBossMaxHp();
	
	playerUIobject = GetRectToCenter(lpPlayer->GetHp()*2 + 50, 80, lpPlayer->GetHp()*4, 18);
	//Rectangle(hdc, playerUIobject.left, playerUIobject.top, playerUIobject.right, playerUIobject.bottom);
	for (int i = 0; i < lpPlayer->GetHp() / 5; i++)
	{
		lpHp01->Render(hdc, 75 + 0 + 18 * i, WINSIZE_HEIGHT / 20 + 41, 0, U_IA_CENTER);
	}
	
	
	// 체력에 따라서 체력바 색상이 달라지게 하고싶다. 어떻게 할까
	if (lpEnemy)
	{
		bossUIobject = GetRectToCenter(lpEnemy->GetHp() / 8 + 50, 50, lpEnemy->GetHp() / 4, 18);
		//Rectangle(hdc, bossUIobject.left, bossUIobject.top, bossUIobject.right, bossUIobject.bottom);
		lpBossHpBar->Render(hdc, WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 20, 0, U_IA_CENTER);
		
		//  /280
	for (int i = 0; i < lpEnemy->GetHp() /70; i++)
		{
			lpHp02->Render(hdc, 75 + 0	 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);
			/*lpHp02->Render(hdc, 75 + 126 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);
			lpHp03->Render(hdc, 75 + 252 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);
			lpHp04->Render(hdc, 75 + 378 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);*/
		}
	}
	//목숨 . 라이프 스톡
	for (int i = 0; i < DataManager::GetSingleton()->GetLifeAmount(); i++)
		lpLifeStock->Render(hdc, 30 + 30 * i, WINSIZE_HEIGHT / 8 + 15, 0, U_IA_CENTER);
	//탄변경
	if (lpPlayer)
		lpMissile[lpPlayer->GetFactoryLine()]->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 70, 0, U_IA_CENTER);
	//메뉴얼
	lpFcukingManual->Render(hdc, WINSIZE_WIDTH -80, WINSIZE_HEIGHT - 100, 0, U_IA_CENTER);
}

//최대치 저장하는 함수
//UI는 바깥에서 값을 참조만 하는것
//UI는 절대로 이런짓을 하면 안된다.
void UIobject::SetBossMaxHp()
{
	if (isMaxHp)
	{
		SetPlayerMaxHp(lpPlayer->GetHp());
		if (lpEnemy) SetBossMaxHp(lpEnemy->GetHp());
		isMaxHp = false;
	}
}