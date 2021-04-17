#pragma once
#include "Factory.h"

class Pattern;
class BasicFactory : public Factory
{
private:
	Pattern* pattern;
	Pattern* pattern2;

private:
	virtual void Init() final;
	virtual void Release() {};
	virtual void Fire(Unit* lpUnit) final;
};

