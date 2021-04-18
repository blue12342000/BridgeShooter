#pragma once
#include "Factory.h"
#include <map>
class Pattern;
class BoomerangFactory :public Factory
{
private:

	enum PatternNum{ normal,boomerang,leftRain,rightRain,topRain,end };
	
private:
	PatternNum patternNum;

	const float phaseTimeSet = 2000.0f;
	const float changeAngleSpeed = 5.0;
	float changeAngle;
	int phase;
	bool isShoot;
	bool isFirst;
	float imsiDeltaTime;
	float missile1Timer;
	float missile2Timer;
	float missile3Timer;
	float missile4Timer;
	float missile5Timer;
	float timer;
private:
	std::map<PatternNum, int>mMissileNum;
	std::map<PatternNum, float>mMissileSpeed;
	std::map<PatternNum, Pattern*>mLpMissilePattern;
	std::map<PatternNum, float>mPhase1Duration;
	std::map<PatternNum, float>mPhase2Duration;
	std::map<PatternNum, float>mPhase3Duration;
private:
	virtual void Init();
	virtual void Release();

	virtual void Fire(Unit* lpUnit);
	void FireBoomerang(Unit* lpUnit);
	void FireNormal(Unit* lpUnit);
	void FireLeftRain(Unit* lpUnit);
	void FireRightRain(Unit* lpUnit);
	void FireTopRain(Unit* lpUnit);
	void FirePhase1(void);
	void FirePhase2(void);
	void FirePhase3(void);
	void CheckFire(void);
};
