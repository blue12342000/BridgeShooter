#pragma once
#include "Factory.h"

class Pattern;
class BasicFactory : public Factory
{
private:
	Pattern* pattern;

public:
	BasicFactory();
	~BasicFactory();

private:
	virtual void Fire(GameObject* lpObject) final;
};

