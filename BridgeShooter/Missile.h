#pragma once
#include "GameObject.h"

class Pattern;
class Animation;
class Unit;
class Missile : public GameObject
{
private:
	int damage;
	Animation* lpAnimation;
	Unit** lpLpTarget;

public:
	float delayTime;

public:	
	void Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render(HDC hdc) override;

	void Move(float deltaTime);

	void SetMissile(string ImageKey, float angle, Transform transform, int size, float delayTime = 0);

	inline void SetDamage(int damage) { this->damage = damage; }
	inline int GetDamage() { return (damage <= 0) ? 1 : damage; }
	inline void SetPattern(Pattern* lpPattern) { this->lpPattern = lpPattern; }
	inline void SetDelayTime(float delayTime) { this->delayTime = delayTime; }
	inline Unit* GetTarget() { return (lpLpTarget)?*lpLpTarget:nullptr; }
	inline void SetLpTarget(Unit** lpLpUnit) { this->lpLpTarget = lpLpUnit; }
};

