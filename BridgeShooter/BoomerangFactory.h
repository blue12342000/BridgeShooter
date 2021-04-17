#pragma once
#include "Factory.h"
class Pattern;
class BoomerangFactory :public Factory
{
private:
	Pattern* lpPattern;
	int missileNum = 16;
private:
	virtual void Init();
	virtual void Release();
	virtual void Fire(Unit* lpUnit);
};
