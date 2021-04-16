#pragma once
#include "GameObject.h"

enum class MISSILE_TYPE
{
	BASIC,
	NONE
};

class Pattern;
class Image;
class Missile : public GameObject
{
public:
	Pattern* lpPattern;
	int frame;
	Image* lpImage; 

public:	
	void Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render(HDC hdc) override;

	void Move(float deltaTime);

	inline void SetPattern(Pattern* lpPattern) { this->lpPattern = lpPattern; }
};

