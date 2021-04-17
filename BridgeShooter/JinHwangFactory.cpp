#include "JinHwangFactory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"

void JinHwangFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::JFCP_NONE);
	vLpPatterns[CREATE_PATTERN::JFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_REFLECT] = new ReflectPattern();

	maxCreateLIne = 0;
}

void JinHwangFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void JinHwangFactory::Fire(Unit* lpUnit)
{
}
