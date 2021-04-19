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
	patternNum = PatternNum::BOOMERANG;
	createLine = 1;
	maxCreateLIne = 3;

	mLpMissilePattern.insert(make_pair(PatternNum::NORMAL, new BasicPattern()));
	mLpMissilePattern.insert(make_pair(PatternNum::BOOMERANG, new BoomerangPattern()));
	mLpMissilePattern.insert(make_pair(PatternNum::L_RAIN, new BasicPattern()));
	mLpMissilePattern.insert(make_pair(PatternNum::rightRain, new BasicPattern()));
	mLpMissilePattern.insert(make_pair(PatternNum::topRain, new BasicPattern()));

	mMissileNum.insert(make_pair(PatternNum::normal,	1));
	mMissileNum.insert(make_pair(PatternNum::boomerang,	16));
	mMissileNum.insert(make_pair(PatternNum::leftRain,	20));
	mMissileNum.insert(make_pair(PatternNum::rightRain,	20));
	mMissileNum.insert(make_pair(PatternNum::topRain,	20));

	mMissileSpeed.insert(make_pair(PatternNum::normal,	300.0f));
	mMissileSpeed.insert(make_pair(PatternNum::boomerang,	170.0f));
	mMissileSpeed.insert(make_pair(PatternNum::leftRain,	150.0f));
	mMissileSpeed.insert(make_pair(PatternNum::rightRain,	150.0f));
	mMissileSpeed.insert(make_pair(PatternNum::topRain,	150.0f));

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
			createLine++;
			if (createLine > 3) {
				createLine = 1;
			}
		}
		changeAngle = lpUnit->angle;
		if (createLine == 1)
		{
			FirePhase1(lpUnit);
			
		}
		else if (createLine ==2)
		{
			FirePhase2(lpUnit);
		}
		else if (createLine == 3)
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
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
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
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
	}
}

void BoomerangFactory::FireLeftRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::leftRain]; i++)// 미사일 ->
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", { 0.0f,(float)(WINSIZE_HEIGHT + 100) * (float)i / mMissileNum[BoomerangFactory::leftRain] },
			{ 0,0 }, 0.0f, mMissileSpeed[BoomerangFactory::leftRain], 10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::leftRain]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
	}
}

void BoomerangFactory::FireRightRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::rightRain]; i++)// 미사일 <-
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", { (float)WINSIZE_WIDTH,(float)(WINSIZE_HEIGHT + 200) * (float)i / mMissileNum[BoomerangFactory::rightRain] },
			{0,0}, PI, mMissileSpeed[BoomerangFactory::rightRain], 10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::rightRain]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
	}
}

void BoomerangFactory::FireTopRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::topRain]; i++)// 미사일 아래로
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", { (float)WINSIZE_WIDTH * (float)i / mMissileNum[BoomerangFactory::topRain] ,0.0f },
			{ 0,0 }, PI / 2.0f, mMissileSpeed[BoomerangFactory::topRain], 10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::topRain]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
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
	
	if (IsCheckTime(timeset.boomerang))
	{
		FireBoomerang(lpUnit);
	}
	
}

void BoomerangFactory::FirePhase3(Unit* lpUnit)
{
	TimeSet timeset;
	changeAngle += PI / 8.0f;
	
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
