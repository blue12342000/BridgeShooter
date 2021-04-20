#include "InGameScene.h"
#include "UIobject.h"
#include "Image.h"
#include "Unit.h""
#include "PlayerController.h"
#include "EnemyGroup.h"
#include "SpaceShip.h"

#include "Planet_SSJ.h"
#include "Planet04.h"
#include "JinHwang.h"
#include "Planet_KMS.h"
#include "Item.h"
#include "Missile.h"
#include "UIobject.h"
#include "GameScene.h"
#include "JinHwangAIContoller.h"
#include "Planet04AIController.h"
#include "SpaceShip_Red.h"
#include "SpaceShip_Gray.h"

void UIobject::Init()
{
	lpImage = ImageManager::GetSingleton()->FindImage("BossHpGauge");

	for (int i = 0; i < 3; i++)
	{
		lpHpCount[i] = ImageManager::GetSingleton()->FindImage("HpCount");
		lpBombCount[i] = ImageManager::GetSingleton()->FindImage("BombCount");
	}//lpMissile[0] lpMissile[1] lpMissile[2]
	lpMissile[0] = ImageManager::GetSingleton()->FindImage("NowMissile_1");
	lpMissile[1] = ImageManager::GetSingleton()->FindImage("NowMissile_2");
	lpMissile[2] = ImageManager::GetSingleton()->FindImage("NowMissile_3");

	lpFcukingManual = ImageManager::GetSingleton()->FindImage("Manual");
	isBossAlive = true;
	isBombUsed = false;
	isBombLeft = true;
	isHpLeft = true;
	isNowMissile = true;
	isPushedManualButton = true;

	playerMaxHp = 0;
	bossMaxHp = 0;	
	//hp =0;
	hpCount = 3;
	//bomb = 0;
	bombAmount = 3;
	fcukingManual = 0;
	index = 0;

	//lpPlayer = new SpaceShip();
	lpPlayer = nullptr;

	lpPlanet04 = new Planet04();
	lpPlanet04->Init();

	lpJinHwang = new Planet_SSJ();
	lpJinHwang->Init();
	lpPlanetSSJ;
	lpPlanetKMS;
	lpEnemyGroup = new EnemyGroup();
	lpEnemyGroup->Init();
	lpSpaceShip = new SpaceShip();
	lpSpaceShip->Init();

	lpSpaceShip_Gray = new SpaceShip_Gray();
	lpSpaceShip_Gray->Init();

	lpSpaceShip_Red = new SpaceShip_Red();
	lpSpaceShip_Red->Init();

}

void UIobject::Release()
{
	/*
	if (KeyManager::GetSingleton()->IsKeyDownOne(VK_OEM_4))
	{
		//이전 이미지로
		lpUIobject->SetIndex(lpUIobject->GetIndex() - 1);
	}
	if (KeyManager::GetSingleton()->IsKeyDownOne(/VK_OEM_6))
	{
		//다음 이미지로
		lpUIobject->SetIndex(lpUIobject->GetIndex() + 1);
	}
	*/
}

void UIobject::Update(float deltaTime)
{
	if (isHpLeft)
	{				//보스가 될 대상을 바꾸고
		SetbossMaxHp(lpJinHwang->hp);
					// 플레이어가될 대상을 바꾸면 값을 따와서 게이지 만듬
		SetPlayerMaxHp(lpSpaceShip->hp);
		isHpLeft = false;
	}
	
	PlayerUIobjectData();
	BossUIobjectData();
	if(lpSpaceShip)
	if (index < 0) index = 2;
	if (index > 2) index = 0;

	
			
	
		//이미지 출력 하나 제거
		
	
}


void UIobject::Render(HDC hdc)
{
	if (lpImage)
	{

		Rectangle(hdc, playerUIobject.left, playerUIobject.top, playerUIobject.right, playerUIobject.bottom);
		// 체력에 따라서 체력바 색상이 달라지게 하고싶다. 어떻게 할까
		if (isBossAlive)
		{
			Rectangle(hdc, bossUIobject.left, bossUIobject.top, bossUIobject.right, bossUIobject.bottom);
			lpImage->Render(hdc, WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 20, 0, U_IA_CENTER);
		}
		if (isBombLeft)
		{
			for (int i = 0; i < bombAmount; i++)
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
		if (isNowMissile)
		{
			if(index == 0)
			lpMissile[0]->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 100, 0, U_IA_CENTER);
			else if(index == 1)
				lpMissile[1]->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 100, 0, U_IA_CENTER);
			else if(index == 2)
				lpMissile[2]->Render(hdc, WINSIZE_WIDTH / 8, WINSIZE_HEIGHT - 100, 0, U_IA_CENTER);
		}
		if (isPushedManualButton)
		{
			lpFcukingManual->Render(hdc, WINSIZE_WIDTH / 10, WINSIZE_HEIGHT / 2, 0, U_IA_CENTER);
		}
	}
}

void UIobject::PlayerUIobjectData()
{
	playerUIobject = GetRectToCenter(playerMaxHp/2 + 50, 100, playerMaxHp, 18);

	//HP가 0되면 값 고정
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

void UIobject::BossUIobjectData()
{
	bossUIobject = GetRectToCenter(bossMaxHp / 2 + 50, 50, bossMaxHp, 18);

	//HP가 0되면 값 고정
	if (bossMaxHp <= 0)
	{
		bossMaxHp = 500;
		isBossAlive = false;
	}
}
void UIobject::IndexData()
{
	//index = GetIndex();
	if (index < 0) index = 2;
	if (index > 2) index = 0;

}
void UIobject::IndexControl(HDC hdc)
{
	

}


void UIobject::HpCount()
{
}

void UIobject::BombCount()
{

	// 값을 낮춰준다
	bombAmount--;
	//0일때 예외
	if (bombAmount < 0)
	{
		bombAmount = 0;
	}
	isBombUsed = false;

}

void UIobject::IsBombUsed()
{
	isBombUsed = true;
}

void UIobject::NowMissile()
{
}

void UIobject::FcukingManual()
{
}


