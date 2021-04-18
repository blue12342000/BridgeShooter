#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class JinHwangFactory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		JFCP_BASIC,
		JFCP_SPIRAL,
		JFCP_REFLECT,
		JFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

private:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Fire(Unit* lpUnit) override;
};
