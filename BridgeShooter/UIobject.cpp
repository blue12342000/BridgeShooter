#include "UIobject.h"
#include "Image.h"
#include "Unit.h""

void UIobject::Init()
{
	elapsedTime = 0;
	lpBossHpBar		= ImageManager::GetSingleton()->FindImage("BossHpGauge");
	lpManual = ImageManager::GetSingleton()->FindImage("Manual");
	lpLifeStock[0]	= ImageManager::GetSingleton()->FindImage("LifeMiniYELLOW");
	lpLifeStock[1]	= ImageManager::GetSingleton()->FindImage("LifeMiniRED");
	lpLifeStock[2]	= ImageManager::GetSingleton()->FindImage("LifeMiniGRAY");
	lpLifeStock[3]  = nullptr;
	lpLifeStock[4]	= ImageManager::GetSingleton()->FindImage("Item_Health");
	lpLifeStock[5]	= ImageManager::GetSingleton()->FindImage("Item_Health");
	lpLifeStock[6]	= ImageManager::GetSingleton()->FindImage("Item_Health");
	lpLifeStock[7]  = ImageManager::GetSingleton()->FindImage("Item_Health");
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
}

void UIobject::Release()
{
	elapsedTime = 0;
}

void UIobject::Update(float deltaTime)
{
	elapsedTime += deltaTime;
}


void UIobject::Render(HDC hdc)
{	
	playerUIobject = GetRectToCenter(lpPlayer->GetHp()*2 + 50, 80, lpPlayer->GetHp()*4, 18);
	//Rectangle(hdc, playerUIobject.left, playerUIobject.top, playerUIobject.right, playerUIobject.bottom);
	for (int i = 0; i < ((float)lpPlayer->GetHp() / lpPlayer->GetMaxHp() * 10.0f); i++)
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
			lpHp02->Render(hdc, 75 + 0 + 18 * i, WINSIZE_HEIGHT / 20 + 11, 0, U_IA_CENTER);
			/*lpHp02->Render(hdc, 75 + 126 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);
			lpHp03->Render(hdc, 75 + 252 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);
			lpHp04->Render(hdc, 75 + 378 + 18 * i, WINSIZE_HEIGHT / 20 +11, 0, U_IA_CENTER);*/
		}
	}
	//목숨 . 라이프 스톡
	for (int i = 0; i < DataManager::GetSingleton()->GetLifeAmount(); i++)
		lpLifeStock[(int)DataManager::GetSingleton()->GetSelectedCharacter()]->Render(hdc, 30 + 30 * i, WINSIZE_HEIGHT / 8 + 15, 0, U_IA_CENTER);
	//탄변경
	if (lpPlayer)
		lpMissile[lpPlayer->GetFactoryLine()]->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 40, 0, U_IA_CENTER);
	//메뉴얼
	if (elapsedTime < 5) lpManual->Render(hdc, WINSIZE_WIDTH -80, WINSIZE_HEIGHT - 80, 0, U_IA_CENTER);
}