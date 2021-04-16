#pragma once
#include"GameObject.h"
class Image;
class Factory;
class Unit:public GameObject
{
private:
	//Collider collider;
	float elapsedTime;
	int frame;
	Image* lpImage;
	Factory* lpFactory;
public:
	virtual void SetFactory(Factory* lpFactory) final;
	virtual void fire(void) final;
};

