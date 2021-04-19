#pragma once
#include "GameObject.h"

class Animation;
class UI : public GameEvent
{
protected:
	Animation* lpAnimation;

public:
	UI() : GameEvent(), lpAnimation(nullptr) {}
	virtual ~UI() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;
};

