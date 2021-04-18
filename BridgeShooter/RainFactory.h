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
		RFCP_RAIN,
		RFCP_SPIRAL,
		RFCP_RSPIRAL,
		RFCP_SINE,
		RFCP_RSINE,
		RFCP_NONE
	};
private:
	vector<Pattern*> vLpPatterns;

	int rnd;

private:
	virtual void Init() final;
	virtual void Release();
	virtual void Fire(Unit* lpUnit) final;
};

