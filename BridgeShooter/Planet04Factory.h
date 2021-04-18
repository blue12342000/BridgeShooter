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
		PLANET04_SPRIAL,
		PLANET04_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

	int rnd;
	int count;
	int bossCount;

	bool isPattern01;
	bool isPattern02;
	bool isPattern03;


private:
	virtual void Init() final;
	virtual void Release() ;
	virtual void Fire(Unit* lpUnit) final;
};

