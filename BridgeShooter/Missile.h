#pragma once
#include "GameObject.h"

class Pattern;
class Animation;
class Image;
class Missile : public GameObject
{
public:
	bool isActive;
	Pattern* lpPattern;
	Image* lpImage;
	Animation* lpAnimation;
	float delayTime;
	MoveInfo deltaMove;

public:	
	void Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render(HDC hdc) override;

	void Move(float deltaTime);

	void SetMissile(string ImageKey, POINTFLOAT pos, POINTFLOAT deltaPos, float angle, float speed, int size, float delayTime = 0);
	void SetMissile(string ImageKey, POINTFLOAT pos, float angle, float speed, int size, float delayTime = 0);
	inline void SetPattern(Pattern* lpPattern) { this->lpPattern = lpPattern; }
	inline void SetDelayTime(float delayTime) { this->delayTime = delayTime; }
};

