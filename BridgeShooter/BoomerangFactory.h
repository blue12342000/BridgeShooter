#pragma once
#include "Factory.h"
#include <map>
class Pattern;
class BoomerangFactory :public Factory
{
private:

	enum PatternNum{ NORMAL,BOOMERANG,L_RAIN,R_RAIN,T_RAIN,END };
	
private:
	PatternNum patternNum;
	float changeAngle;
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
	void FirePhase1(Unit* lpUnit);
	void FirePhase2(Unit* lpUnit);
	void FirePhase3(Unit* lpUnit);
};
