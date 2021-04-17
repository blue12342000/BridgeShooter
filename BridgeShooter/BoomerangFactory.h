#pragma once
#include "Factory.h"
class Pattern;
class BoomerangFactory :public Factory
{
private:
	Pattern* lpPattern;

private:
	virtual void Init();
	virtual void Release();
	virtual void Fire(Unit* lpUnit);
};
