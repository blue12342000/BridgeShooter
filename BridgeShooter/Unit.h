#pragma once
#include"GameObject.h"

class HpGauge;
class Animation;
class Factory;
class Pattern;
class Unit : public GameObject
{
protected:
	Animation* lpAnimation;
	Factory* lpFactory;
	Pattern* lpPattern;
	Unit* lpTarget;
	POINTFLOAT force;
	int factoryLine;
	bool isInertia;
	HpGauge* lphpGauge;

public:
	Unit(): GameObject(), lpAnimation(nullptr), lpFactory(nullptr), lpTarget(nullptr), factoryLine(0), isInertia(false){}
	virtual ~Unit() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual void Fire() final;
	virtual void Translate(POINTFLOAT force) final;
	virtual void ChangeFactoryLine(int delta) final;
	virtual void ToggleInertia() final { isInertia = !isInertia; }

	virtual void SetFactory(Factory* lpFactory) final;
	virtual void SetFactoryLine(int factoryLine) final;

	inline void SetTarget(Unit* lpTarget) { this->lpTarget = lpTarget; }
	inline void SetInetia(bool isInertia) { this->isInertia = isInertia; }
};

