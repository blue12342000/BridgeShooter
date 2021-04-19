#pragma once
#include"GameObject.h"

class Animation;
class UI : public GameObject
{
protected:
	Animation* lpAnimation;

public:
	UI() : GameObject(), lpAnimation(nullptr){}
	virtual ~UI() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
};

