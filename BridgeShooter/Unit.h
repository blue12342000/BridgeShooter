#pragma once
#include"GameObject.h"

enum class UNIT_STATE
{
	IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	NONE
};

class Image;
class Factory;
class Unit : public GameObject
{
protected:
	UNIT_STATE state;
	int frame;
	float motionTimer;
	float motionSpeed;
	Image* lpImage;
	Factory* lpFactory;

public:
	Unit(): GameObject(), frame(0), lpImage(nullptr), lpFactory(nullptr) {}
	virtual ~Unit() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual void SetFactory(Factory* lpFactory) final;
	virtual void Fire(void) final;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
};

