#pragma once
#include "Factory.h"

class Pattern;
class SSJFactory : public Factory
{
private:
	Pattern* pattern1;
	Pattern* pattern2;
	Pattern* pattern3;
	Pattern* pattern4;

public:
	virtual void Init();
	virtual void Release();
	virtual void Fire(Unit* lpUnit);
	
};

