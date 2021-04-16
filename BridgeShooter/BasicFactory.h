#pragma once
#include "Factory.h"

class Pattern;
class BasicFactory : public Factory
{
private:
	Pattern* pattern;

private:
	virtual void Fire(GameObject* lpObject) final;
};

