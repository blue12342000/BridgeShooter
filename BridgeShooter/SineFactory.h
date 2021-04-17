#pragma once
#include "Factory.h"

class Pattern;
class SineFactory : public Factory
{
private:
	Pattern* pattern;

public:
	SineFactory();
	~SineFactory();

private:
	virtual void Fire(GameObject* lpObject) final;
};

