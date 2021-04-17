#include "JinHwangFactory.h"


void JinHwangFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::BFCP_NONE);
	vLpPatterns[CREATE_PATTERN::BFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::BFCP_REFLECT] = new ReflectPattern();

	maxCreateLIne = 3;
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
