#pragma once
#include "Factory.h"

class Pattern;
class RainFactory : public Factory
{
private:
	Pattern* pattern;

private:
	virtual void Init() final;
	virtual void Release() {};
	virtual void Fire(Unit* lpUnit) final;
};

