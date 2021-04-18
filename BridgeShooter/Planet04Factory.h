#pragma once
#include "Factory.h"

class Pattern;
class Planet04Factory : public Factory
{
private:
	Pattern* pattern;
	Pattern* pattern2;
	int rnd;
	int count;

private:
	virtual void Init() final;
	virtual void Release() {};
	virtual void Fire(Unit* lpUnit) final;
};

