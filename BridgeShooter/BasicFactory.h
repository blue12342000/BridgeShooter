#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class BasicFactory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		BFCP_BASIC,
		BFCP_REFLECT,
		BFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

private:
	virtual void Init() final;
	virtual void Release();
	virtual void Fire(Unit* lpUnit) final;
};

