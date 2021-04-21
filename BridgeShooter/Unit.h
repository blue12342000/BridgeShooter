#pragma once
#include"GameObject.h"

class Animation;
class Factory;
class Unit : public GameObject
{
protected:
	bool isReady;
	UNIT_KIND kind;
	Animation* lpAnimation;
	Factory* lpFactory;
	Unit* lpTarget;
	POINTFLOAT force;
	int factoryLine;
	bool isInertia;

	float hp;
	float maxHp;
	int bomb;

public:
	Unit(): GameObject(), isReady(false), lpAnimation(nullptr), lpFactory(nullptr), lpTarget(nullptr), factoryLine(0), isInertia(false), hp(0), bomb(0){}
	virtual ~Unit() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual bool Hit(int damage) final;
	virtual void Fire() final;
	virtual void Translate(POINTFLOAT force) final;
	virtual void ChangeFactoryLine(int delta, bool isLoop = true) final;
	virtual void ToggleInertia() final { isInertia = !isInertia; }

	virtual void ResetTimer() final;
	inline void Heal(int heal) { hp += heal; if (hp > maxHp) hp = maxHp; }

	virtual void SetFactory(Factory* lpFactory) final;
	virtual void SetFactoryLine(int factoryLine) final;

	inline bool IsAlive() { return hp > FLT_EPSILON; }
	inline int GetFactoryLine() {return factoryLine; }
	inline int GetBomb() { return bomb; }
	inline void SetTarget(Unit* lpTarget) { this->lpTarget = lpTarget; }
	inline Unit*& GetTarget() { return lpTarget; }
	inline void SetInetia(bool isInertia) { this->isInertia = isInertia; }
	inline Animation* GetLpAnimation() { return lpAnimation; }
	inline bool IsReady() { return isReady; }
	inline void SetIsReady(bool isReady) { this->isReady = isReady; }
	inline void SetUnitKind(UNIT_KIND kind) { this->kind = kind; }
	inline UNIT_KIND GetUnitKind() { return this->kind; }
	inline int GetHp() { return hp; }
	inline int GetMaxHp() { return maxHp; }
};

