#pragma once
#include "Factory.h"

class Pattern;
class SineFactory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		SFCP_SINE,
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

