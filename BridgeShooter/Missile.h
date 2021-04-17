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
	bool isActive;
	Pattern* lpPattern;
	int frame;
	Image* lpImage;

	float delayTime;
	MoveInfo deltaMove;

public:	
	void Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render(HDC hdc) override;

	void Move(float deltaTime);

	inline void SetPattern(Pattern* lpPattern) { this->lpPattern = lpPattern; }
	inline void SetDelayTime(float delayTime) { this->delayTime = delayTime; }
};

