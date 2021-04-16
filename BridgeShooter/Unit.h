#pragma once
#include"GameObject.h"
class Image;
class Factory;
class Unit : public GameObject
{
protected:
	int frame;
	Image* lpImage;
	Factory* lpFactory;

public:
	Unit(): GameObject(), frame(0), lpImage(nullptr), lpFactory(nullptr) {}
	virtual ~Unit() {}

	virtual void Init()  override;
	virtual void Update(float deltaTime)  override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	virtual void SetFactory(Factory* lpFactory) final;
	virtual void fire(void) final;
};

