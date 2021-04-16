#pragma once
#include"GameObject.h"
class Image;
class Pattern;
class Factory
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

