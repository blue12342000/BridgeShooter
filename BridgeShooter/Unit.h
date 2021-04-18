#pragma once
#include"GameObject.h"

class Animation;
class Factory;
class Unit : public GameObject
{
protected:
	Animation* lpAnimation;
	Factory* lpFactory;

public:
	Unit(): GameObject(), lpAnimation(nullptr), lpFactory(nullptr) {}
	virtual ~Unit() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual void SetFactory(Factory* lpFactory) final;
	virtual void Fire(void) final;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
};

