#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class Planet04Factory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		PLANET04_BASIC,
		PLANET04_RAIN,
		PLANET04_REFLECT,
		PLANET04_SINE,
		PLANET04_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

	int count;
	int bossCount;

private:
	virtual void Init();
	virtual void Release() ;
	virtual void Fire(Unit* lpUnit);
};

