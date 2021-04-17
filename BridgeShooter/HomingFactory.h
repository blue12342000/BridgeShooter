#pragma once
#include "Factory.h"

class Pattern;
class HomingFactory : public Factory
{
private:
	Pattern* pattern;

public:
	HomingFactory();
	~HomingFactory();

private:
	virtual void Fire(GameObject* lpObject) final;
};

