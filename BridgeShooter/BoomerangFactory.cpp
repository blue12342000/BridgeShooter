#include "BoomerangFactory.h"
#include "Pattern.h"
#include"BoomerangPattern.h"
#include"NormalPattern.h"
#include"Missile.h"
#include "Unit.h"

//enum PatternNum{ normal,boomerang,leftRain,rightRain,topRain,end }; <- 참고용
void BoomerangFactory::Init()
{
	patternNum = PatternNum::boomerang;
	phase = 1;
	imsiDeltaTime = 0.0;
	timer = 0.0;
	missile1Timer=0.0;
	isShoot = false;

	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::normal, new NormalPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::boomerang, new BoomerangPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::leftRain, new NormalPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::rightRain, new NormalPattern()));
	mLpMissilePattern.insert(pair<PatternNum, Pattern*>(PatternNum::topRain, new NormalPattern()));

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
		imsiDeltaTime+=0.001f;
		if (imsiDeltaTime >= 1.0f) {
			imsiDeltaTime -= 1.0f;
		}
		timer += imsiDeltaTime;
		if (timer>= phaseTimeSet)
		{
			timer -= phaseTimeSet;
			++phase;
			if (phase>3)
			{
				phase = 1;
			}
		}
		changeAngle = lpUnit->angle;
		if (phase==1)
		{
			missile1Timer += imsiDeltaTime;
			changeAngle += imsiDeltaTime* changeAngleSpeed;
			while (missile1Timer >= 20.0f)
			{
				missile1Timer -= 20.0f;
				isShoot = false;
			}
			if (changeAngle>(2*PI)) 
			{
				changeAngle -= (2 * PI);
			}
			if (!isShoot) 
			{
				patternNum = PatternNum::boomerang;
				isShoot = true;
			}
			else 
			{
				patternNum = PatternNum::end;
			}
			
			isShoot;
		}
		else if (phase == 2) 
		{
			patternNum = PatternNum::end;
		}
		else if (phase == 3)
		{
			patternNum = PatternNum::end;
		}
		switch (patternNum)
		{
		case BoomerangFactory::normal:
			FireNormal(lpUnit);
			break;
		case BoomerangFactory::boomerang:
			FireBoomerang(lpUnit);
			break;
		case BoomerangFactory::leftRain:
			FireLeftRain(lpUnit);
			break;
		case BoomerangFactory::rightRain:
			FireRightRain(lpUnit);
			break;
		case BoomerangFactory::topRain:
			FireTopRain(lpUnit);
			break;
		}
		
	}
	
}

void BoomerangFactory::FireBoomerang(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::boomerang]; i++)//부메랑패턴
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = 2 * PI * i / mMissileNum[BoomerangFactory::boomerang]+ changeAngle;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::boomerang];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::boomerang]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireNormal(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::normal]; i++)//일반 미사일
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = lpUnit->angle;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::normal];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::normal]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireLeftRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::leftRain]; i++)// 미사일 ->
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = { 0.0f,(float)WINSIZE_HEIGHT * (float)i / mMissileNum[BoomerangFactory::leftRain] };
		lpMissile->angle = 0.0f;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::leftRain];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::leftRain]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireRightRain(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::rightRain]; i++)// 미사일 <-
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = { (float)WINSIZE_WIDTH,(float)WINSIZE_HEIGHT * (float)i / mMissileNum[BoomerangFactory::rightRain] };
		lpMissile->angle = PI;
		lpMissile->speed = mMissileSpeed[BoomerangFactory::rightRain];
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::rightRain]);
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
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}
