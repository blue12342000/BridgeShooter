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

	const float phaseTimeSet = 15.0;
	const float changeAngleSpeed = 5.0;
	float changeAngle;
	int phase;
	bool isShoot;
	float imsiDeltaTime;
	float missile1Timer;
	float timer;
private:
	std::map<PatternNum, int>mMissileNum;
	std::map<PatternNum, float>mMissileSpeed;
	std::map<PatternNum, Pattern*>mLpMissilePattern;
private:
	virtual void Init();
	virtual void Release();

	virtual void Fire(Unit* lpUnit);
	void FireBoomerang(Unit* lpUnit);
	void FireNormal(Unit* lpUnit);
	void FireLeftRain(Unit* lpUnit);
	void FireRightRain(Unit* lpUnit);
	void FireTopRain(Unit* lpUnit);
};
