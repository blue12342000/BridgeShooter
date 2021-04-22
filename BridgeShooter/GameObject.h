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

	void SetHitBox(POINTFLOAT pos, int width = -1, int height = -1)
	{
		if (width > 0)
		{
			this->width = width;
			hitBox.left = (int)(pos.x - width / 2);
			hitBox.right = (int)(pos.x + width / 2);
		}
		else
		{
			hitBox.left = (int)(pos.x - this->width / 2);
			hitBox.right = (int)(pos.x + this->width / 2);
		}

		if (height > 0)
		{
			this->height = height;
			hitBox.top = (int)(pos.y - height / 2);
			hitBox.bottom = (int)(pos.y + height / 2);
		}
		else
		{
			
			hitBox.top = (int)(pos.y - this->height / 2);
			hitBox.bottom = (int)(pos.y + this->height / 2);
		}
	}
};

/*
* POINTFLOAT 이동 시작점
* float 이동 각도
* float 이동 속도
* float 진동 주기
* float 진폭
*/
struct Transform
{
	POINTFLOAT pos;
	float angle;
	float speed;
	float period;
	float amplitude;
};

interface GameEvent
{
public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Release() = 0;
	virtual void Render(HDC hdc) = 0;
};

class Pattern;
class GameObject : public GameEvent
{
public:
	float elapsedTime;
	float angle;
	Collider collider;
	POINTFLOAT pos;

	Transform transform;
	Pattern* lpPattern;
	
public:
	GameObject() :elapsedTime(0), angle(0), collider(Collider()), pos({0, 0}), lpPattern(nullptr), transform(Transform{}) {}
	virtual ~GameObject() {}

	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void Release() {}
	virtual void Render(HDC hdc) {}
};