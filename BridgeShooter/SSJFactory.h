#pragma once
#include "Factory.h"
#include "BridgeShooter.h"

class Pattern;
class SSJFactory : public Factory
{
private:
	enum CREATE_PATTERN
	{
		SFCP_BASIC,
		SFCP_SPIRAL,
		SFCP_REVERSE_SPIRAL,
		SFCP_SINE,
		SFCP_REFLECT,
		SFCP_DELAYBASIC,
		SFCP_NONE
	};

private:
	vector<Pattern*> vLpPatterns;

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

