#pragma once
#include "Factory.h"

class Pattern;
class SSJFactory : public Factory
{
private:
	Pattern* pattern1;

public:
	virtual void Init();
	virtual void Release();
	virtual void Fire(Unit* lpUnit);
	
};

