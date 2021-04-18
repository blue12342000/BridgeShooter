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
	Pattern* pattern5;
	Pattern* pattern6;

	float delayTime_0;
	float delayTime_1;
	int delayTime_2;
	bool patternArray[200] = { 1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,
								1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,0,0,1,1,1,
								1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,
								1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
								1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1};
	int phaseChanger;

public:
	virtual void Init();
	virtual void Release();
	virtual void Fire(Unit* lpUnit);
	
};

