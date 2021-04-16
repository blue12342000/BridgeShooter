#pragma once
#include "GameObject.h"

class Pattern;
class Image;
class Missile : public GameObject
{
private:
	Pattern* lpPattern;
	//콜라이더
	float elapsedTime;
	int frame;
	Image* lpImage; 

public:	
	void Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render(HDC hdc) override;

	void Move(float deltaTime);
	void SetPattern(Pattern* lpPattern);
};

