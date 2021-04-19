#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class SpaceShipFactory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		SFCP_BASIC,
		SFCP_REFLECT,
		SFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

private:
	virtual void Init() final;
	virtual void Release();
	virtual void Fire(Unit* lpUnit) final;
};

