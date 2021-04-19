
#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class Planet_KMS_Factory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		KFCP_BASIC,
		KFCP_BOOMERANG,
		KFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

private:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Fire(Unit* lpUnit) override;
};