#pragma once
#include "Factory.h"

class Pattern;
class SSJFactory : public Factory
{
private:
	Pattern* lpPattern1;
	Pattern* lpPattern2;
	Pattern* lpPattern3;
	Pattern* lpPattern4;
	Pattern* lpPattern5;
	Pattern* lpPattern6;

	int delayTime_0;

	bool patternArray[200] = { 1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,
								1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,0,0,1,1,1,
								1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,
								1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1};
	int phaseChanger;

public:
	virtual void Init();
	virtual void Release();
	virtual void Fire(Unit* lpUnit);
	
};

