#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class JinHwangFactory : public Factory
{
private:
	struct BluePrint
	{
		float angle;
		float speed;
		string imageKey;

	};

	enum CREATE_PATTERN
	{
		JFCP_BASIC,
		JFCP_SPIRAL,
		JFCP_REVERSE_SPIRAL,
		JFCP_REFLECT,
		JFCP_BOOMERANG,
		JFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

private:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Fire(Unit* lpUnit) override;
};

