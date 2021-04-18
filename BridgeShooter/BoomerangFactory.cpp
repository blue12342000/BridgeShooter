#include "BoomerangFactory.h"
#include "Pattern.h"
#include"BoomerangPattern.h"
#include"BasicPattern.h"
#include"Missile.h"
#include<ctime>
#include "Unit.h"

//enum PatternNum{ normal,boomerang,leftRain,rightRain,topRain,end }; <- 참고용
void BoomerangFactory::Init()
{
	patternNum = PatternNum::boomerang;
	phase = 1;
	imsiDeltaTime = 0.0;
	timer = 0.0;
	isFirst = true;
	missile1Timer=0.0;
	missile2Timer = 0.0;
	missile3Timer = 0.0;
	missile4Timer = 0.0;
	missile5Timer = 0.0;
	isShoot = false;

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

	mPhase1Duration.insert(pair<PatternNum, float>(PatternNum::normal, 1.0f));
	mPhase1Duration.insert(pair<PatternNum, float>(PatternNum::boomerang, NULL));
	mPhase1Duration.insert(pair<PatternNum, float>(PatternNum::leftRain, NULL));
	mPhase1Duration.insert(pair<PatternNum, float>(PatternNum::rightRain, NULL));
	mPhase1Duration.insert(pair<PatternNum, float>(PatternNum::topRain, NULL));

	mPhase2Duration.insert(pair<PatternNum, float>(PatternNum::normal, NULL));
	mPhase2Duration.insert(pair<PatternNum, float>(PatternNum::boomerang, 200.0f));
	mPhase2Duration.insert(pair<PatternNum, float>(PatternNum::leftRain, NULL));
	mPhase2Duration.insert(pair<PatternNum, float>(PatternNum::rightRain, NULL));
	mPhase2Duration.insert(pair<PatternNum, float>(PatternNum::topRain, NULL));

	mPhase3Duration.insert(pair<PatternNum, float>(PatternNum::normal, NULL));
	mPhase3Duration.insert(pair<PatternNum, float>(PatternNum::boomerang, 600.0f));
	mPhase3Duration.insert(pair<PatternNum, float>(PatternNum::leftRain, 300.0f));
	mPhase3Duration.insert(pair<PatternNum, float>(PatternNum::rightRain, 320.0f));
	mPhase3Duration.insert(pair<PatternNum, float>(PatternNum::topRain, 450.0f));

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
	if (mPhase1Duration.size()) {
		for (std::map<PatternNum, float>::iterator i = mPhase1Duration.begin(); i != mPhase1Duration.end();)
		{
			i = mPhase1Duration.erase(i);
		}
	}
	if (mPhase2Duration.size()) {
		for (std::map<PatternNum, float>::iterator i = mPhase2Duration.begin(); i != mPhase2Duration.end();)
		{
			i = mPhase2Duration.erase(i);
		}
	}
	if (mPhase3Duration.size()) {
		for (std::map<PatternNum, float>::iterator i = mPhase3Duration.begin(); i != mPhase3Duration.end();)
		{
			i = mPhase3Duration.erase(i);
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
			isFirst = true;
			timer -= phaseTimeSet;
			++phase;
			if (phase>3)
			{
				phase = 1;
			}
		}
		changeAngle = lpUnit->angle;
		if (phase == 1)
		{
			FirePhase1();
			
		}
		else if (phase==2)
		{
			FirePhase2();
		}
		else if (phase == 3)
		{
			FirePhase3();
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
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos,
			2 * PI * i / mMissileNum[BoomerangFactory::boomerang] + changeAngle,
			mMissileSpeed[BoomerangFactory::boomerang],10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::boomerang]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}

void BoomerangFactory::FireNormal(Unit* lpUnit)
{
	for (int i = 0; i < mMissileNum[BoomerangFactory::normal]; i++)//일반 미사일
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos,
			lpUnit->angle + changeAngle,
			mMissileSpeed[BoomerangFactory::normal], 10);
		lpMissile->SetPattern(mLpMissilePattern[BoomerangFactory::normal]);
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

void BoomerangFactory::FirePhase1(void)
{
	CheckFire();
	missile1Timer += imsiDeltaTime;
	changeAngle =(rand()%(int)(2*PI*1000))/1000.0f;
	if (missile1Timer >= mPhase1Duration[BoomerangFactory::normal])
	{
		missile1Timer -= mPhase1Duration[BoomerangFactory::normal];
		isShoot = false;
	}
	if (changeAngle > (2 * PI))
	{
		changeAngle -= (2 * PI);
	}
	if (!isShoot)
	{
		patternNum = PatternNum::normal;
		isShoot = true;
	}
	else
	{
		patternNum = PatternNum::end;
	}
}

void BoomerangFactory::FirePhase2(void)
{
	CheckFire();
	missile2Timer += imsiDeltaTime;
	changeAngle += imsiDeltaTime * changeAngleSpeed;
	if (missile2Timer >= mPhase2Duration[BoomerangFactory::boomerang])
	{
		missile2Timer -= mPhase2Duration[BoomerangFactory::boomerang];
		isShoot = false;
	}
	if (changeAngle > (2 * PI))
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
}

void BoomerangFactory::FirePhase3(void)
{
	CheckFire();
	PatternNum patNum= PatternNum::end;
	missile1Timer += imsiDeltaTime;
	missile2Timer += imsiDeltaTime;
	missile3Timer += imsiDeltaTime;
	missile4Timer += imsiDeltaTime;
	changeAngle += imsiDeltaTime * changeAngleSpeed;
	if (missile1Timer >= mPhase3Duration[BoomerangFactory::boomerang])
	{
		missile1Timer -= mPhase3Duration[BoomerangFactory::boomerang];
		patNum = PatternNum::boomerang;
		isShoot = false;
	}
	if (missile2Timer >= mPhase3Duration[BoomerangFactory::rightRain])
	{
		missile2Timer -= mPhase3Duration[BoomerangFactory::rightRain];
		patNum = PatternNum::rightRain;
		isShoot = false;
	}
	if (missile3Timer >= mPhase3Duration[BoomerangFactory::leftRain])
	{
		missile3Timer -= mPhase3Duration[BoomerangFactory::leftRain];
		patNum = PatternNum::leftRain;
		isShoot = false;
	}
	if (missile4Timer >= mPhase3Duration[BoomerangFactory::topRain])
	{
		missile4Timer -= mPhase3Duration[BoomerangFactory::topRain];
		patNum = PatternNum::topRain;
		isShoot = false;
	}
	if (changeAngle > (2 * PI))
	{
		changeAngle -= (2 * PI);
	}
	if (!isShoot)
	{
		patternNum = patNum;
		isShoot = true;
	}
	else
	{
		patternNum = PatternNum::end;
	}
}

void BoomerangFactory::CheckFire(void)
{
	if (isFirst) {
		srand(time(NULL));
		missile1Timer = 0.0f;
		missile5Timer = 0.0f;
		missile4Timer = 0.0f;
		missile3Timer = 0.0f;
		missile2Timer = 0.0f;
		changeAngle = 0.0f;
		isFirst = false;
	}
}
