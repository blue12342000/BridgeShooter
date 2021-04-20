#pragma once
#include"GameObject.h"

struct Force
{
	float force;
	POINT dir;
};

class HpGauge;
class Animation;
class Factory;
class Unit : public GameObject
{
protected:
	Animation* lpAnimation;
	Factory* lpFactory;
	Unit* lpTarget;
	Force force;
	HpGauge* lpHpGauge;

public:
	Unit(): GameObject(), lpAnimation(nullptr), lpFactory(nullptr), lpTarget(nullptr) {}
	virtual ~Unit() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual void Fire() final;
	virtual void Translate(Force force) final;

	virtual void SetFactory(Factory* lpFactory) final;

	inline void SetTarget(Unit* lpTarget) { this->lpTarget = lpTarget; }
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void SetAngle(float angle) { this->angle = angle; }
};

