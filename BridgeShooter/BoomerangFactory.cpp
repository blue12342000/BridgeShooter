#include "BoomerangFactory.h"
#include "Pattern.h"
#include"BoomerangPattern.h"
#include"BasicPattern.h"
#include"Missile.h"
#include<ctime>
#include "Unit.h"



struct TimeSet
{
	const int phase = 10000;
	const int boomerang = 2000;
	const int rain = 3000;
	const int normal = 2;
};
void BoomerangFactory::Init()
{
	TimeSet timeset;
	patternNum = PatternNum::boomerang;
	phase = 1;


	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::normal, new BasicPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::boomerang, new BoomerangPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::leftRain, new BasicPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::rightRain, new BasicPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::topRain, new BasicPattern()));

	mMissileNum.insert(pair<PatternNum, int>(PatternNum::normal,	1));
	mMissileNum.insert(pair<PatternNum, int>(PatternNum::boomerang,	16));
	mMissileNum.insert(pair<PatternNum, int>(PatternNum::leftRain,	20));
	mMissileNum.insert(pair<PatternNum, int>(PatternNum::rightRain,	20));
	mMissileNum.insert(pair<PatternNum, int>(PatternNum::topRain,	20));

	mMissileSpeed.insert(pair<PatternNum, float>(PatternNum::normal,	300.0f));
	mMissileSpeed.insert(pair<PatternNum, float>(PatternNum::boomerang,	170.0f));
	mMissileSpeed.insert(pair<PatternNum, float>(PatternNum::leftRain,	150.0f));
	mMissileSpeed.insert(pair<PatternNum, float>(PatternNum::rightRain,	150.0f));
	mMissileSpeed.insert(pair<PatternNum, float>(PatternNum::topRain,	150.0f));

	SetCheckTime(timeset.phase);
	SetCheckTime(timeset.boomerang);
	SetCheckTime(timeset.rain);
	SetCheckTime(timeset.normal);
}

void BoomerangFactory::Release()
{

	if (mMissileNum.size()) {
		for (std::map<PatternNum, int>::iterator i = mMissileNum.begin(); i != mMissileNum.end(); )
		{
			i=mMissileNum.erase(i);
		}
	}
	if (mMissileSpeed.size()) {
		for (std::map<PatternNum, float>::iterator i = mMissileSpeed.begin(); i != mMissileSpeed.end(); )
		{
			i=mMissileSpeed.erase(i);
		}
	}
	if (mLpMissilePattern.size()) {
		for (std::map<PatternNum, Pattern*>::iterator i = mLpMissilePattern.begin(); i != mLpMissilePattern.end();)
		{
			i=mLpMissilePattern.erase(i);
		}
	}
	
}

void BoomerangFactory::Fire(Unit* lpUnit)
{
	if (lpUnit) {
		TimeSet timeset;
		if (IsCheckTime(timeset.phase)) {
			phase++;
			if (phase > 3) {
				phase = 1;
			}
		}
		changeAngle = lpUnit->angle;
		if (phase == 1)
		{
			FirePhase1(lpUnit);
			
		}
		else if (phase==2)
		{
			FirePhase2(lpUnit);
		}
		else if (phase == 3)
		{
			FirePhase3(lpUnit);
		}
		
	}
	
}

void BoomerangFactory::FireBoomerang(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::boomerang]; i++)//부메랑패턴
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpMissile->deltaMove.deltaPos,
			2 * PI * i / mMissileNum[BoomerangFactory::boomerang] + changeAngle,
			mMissileSpeed[BoomerangFactory::boomerang],10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::boomerang]);
		lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireNormal(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::normal]; i++)//일반 미사일
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpMissile->deltaMove.deltaPos,
			lpUnit->angle + changeAngle,
			mMissileSpeed[BoomerangFactory::normal], 10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::normal]);
		lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireLeftRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::leftRain]; i++)// 미사일 ->
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = { 0.0f,(float)(WINSIZE_HEIGHT + 100) * (float)i / mMissileNum[BoomerangFactory::leftRain]  };
		lpMissile->angle = 0.0f;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::leftRain];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::leftRain]);
		lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireRightRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::rightRain]; i++)// 미사일 <-
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = { (float)WINSIZE_WIDTH,(float)(WINSIZE_HEIGHT+200) * (float)i / mMissileNum[BoomerangFactory::rightRain] };
		lpMissile->angle = PI;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::rightRain];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::rightRain]);
		lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireTopRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::topRain]; i++)// 미사일 아래로
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = { (float)WINSIZE_WIDTH * (float)i / mMissileNum[BoomerangFactory::topRain] ,0.0f};
		lpMissile->angle = PI/2.0f;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::topRain];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::topRain]);
		lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FirePhase1(Unit* lpUnit)
{
	TimeSet timeset;
	changeAngle = (rand() % (int)(2 * PI * 1000)) / 1000.0f;
	if (IsCheckTime(timeset.normal)) 
	{
		FireNormal(lpUnit);
	}
}

void BoomerangFactory::FirePhase2(Unit* lpUnit)
{
	TimeSet timeset;
	changeAngle += PI/8.0f;
	if (changeAngle >= (2 * PI)) {
		changeAngle -= (2 * PI);
	}
	if (IsCheckTime(timeset.boomerang))
	{
		FireBoomerang(lpUnit);
	}
	
}

void BoomerangFactory::FirePhase3(Unit* lpUnit)
{
	TimeSet timeset;
	changeAngle += PI / 8.0f;
	if (changeAngle >= (2 * PI)) {
		changeAngle -= (2 * PI);
	}
	if (IsCheckTime(timeset.boomerang))
	{
		FireBoomerang(lpUnit);
	}
	if (IsCheckTime(timeset.rain))
	{
		FireLeftRain(lpUnit);
		FireRightRain(lpUnit);
		FireTopRain(lpUnit);
	}

}
