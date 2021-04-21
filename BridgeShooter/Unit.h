#pragma once
#include"GameObject.h"

class UIobject;
class Animation;
class Factory;
class Pattern;
class Unit : public GameObject
{
protected:
	Animation* lpAnimation;
	Factory* lpFactory;
	Unit* lpTarget;
	POINTFLOAT force;
	int factoryLine;
	bool isInertia;

	int hp;

	UIobject* lpUIobject;
	float hp;
	int bomb;

public:
	Unit(): GameObject(), lpAnimation(nullptr), lpFactory(nullptr), lpTarget(nullptr), factoryLine(0), isInertia(false), hp(0), bomb(0){}
	virtual ~Unit() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual void Fire() final;
	virtual void Translate(POINTFLOAT force) final;
	virtual void ChangeFactoryLine(int delta) final;
	virtual void ToggleInertia() final { isInertia = !isInertia; }

	virtual void ResetTimer() final;

	virtual void SetFactory(Factory* lpFactory) final;
	virtual void SetFactoryLine(int factoryLine) final;
	virtual void SetHp(float hp) final { this->hp = hp; };

	inline int GetFactoryLine() {return factoryLine; }
	inline float GetHp() { return hp; }
	inline int GetBomb() { return bomb; }

	inline void SetTarget(Unit* lpTarget) { this->lpTarget = lpTarget; }
	inline Unit*& GetTarget() { return lpTarget; }
	inline void SetInetia(bool isInertia) { this->isInertia = isInertia; }
	inline Animation* GetLpAnimation() { return lpAnimation; }
	inline int GetHP() { return hp; }
};

