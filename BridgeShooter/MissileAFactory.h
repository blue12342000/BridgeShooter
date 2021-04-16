#pragma once
#include"Factory.h"
class MissileAFactory:public Factory
{
private:
	//Collider collider;
	float elapsedTimer;
	int frame;
	Pattern* lpPattern;
	Image* lpImage;
	
public:
	virtual void Fire(GameObject* lpObject) {};
};

