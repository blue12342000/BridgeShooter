#pragma once
#include "BridgeShooter.h"

enum class COLLIDER_TYPE
{
	RECTANGLE,
	CIRCLE,
	NONE
};

struct Collider
{
	COLLIDER_TYPE type;
	int width;
	int height;
	RECT hitBox;
};

class GameObject
{
public:
	POINTFLOAT pos;
	float angle;
	float speed;
	Collider collider;
	float elapsedTime;

public:
	GameObject() :pos({ 0,0 }), angle(0), speed(0), collider(Collider()), elapsedTime(0) {}
	virtual ~GameObject() {}

	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void Release() {}
	virtual void Render(HDC hdc) {}
};