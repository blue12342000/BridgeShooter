#pragma once
#include "Factory.h"

class Pattern;
class RainFactory : public Factory
{
private:
	Pattern* pattern;
	Pattern* pattern2;
	int rnd;

private:
	virtual void Init() final;
	virtual void Release() {};
	virtual void Fire(Unit* lpUnit) final;
};
