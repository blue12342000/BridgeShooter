#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class RainFactory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		RFCP_BASIC,
		RFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;
	vector<string> vMissileKey;
	int missileCount;

private:
	virtual void Init() final;
	virtual void Release();
	virtual void Fire(Unit* lpUnit) final;
};

