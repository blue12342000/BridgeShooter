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

	void SetHitBox(POINTFLOAT pos, POINTFLOAT deltaPos = { 0,0 }, int width = -1, int height = -1)
	{
		//width 값 갱신 this에 있는 내 width 값으로
		if (width > 0)
		{
			this->width = width;
			hitBox.left = (int)(pos.x + deltaPos.x - width / 2);
			hitBox.right = (int)(pos.x + deltaPos.x + width / 2);
		}
		else
		{
			hitBox.left = (int)(pos.x  + deltaPos.x - this->width / 2);
			hitBox.right = (int)(pos.x  + deltaPos.x + this->width / 2);
		}

		if (height > 0)
		{
			this->height = height;
			hitBox.top = (int)(pos.y + deltaPos.y - height / 2);
			hitBox.bottom = (int)(pos.y + deltaPos.y + height / 2);
		}
		else
		{
			
			hitBox.top = (int)(pos.y + deltaPos.y - this->height / 2);
			hitBox.bottom = (int)(pos.y + deltaPos.y + this->height / 2);
		}
	}
};

struct MoveInfo
{
	float angle;
	POINTFLOAT deltaPos;
};

interface GameEvent
{
public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Release() = 0;
	virtual void Render(HDC hdc) = 0;
};

class GameObject : public GameEvent
{
public:
	POINTFLOAT origin;
	POINTFLOAT pos;
	float originAngle;
	float angle;
	float speed;
	float period;
	float amplitude;
	Collider collider;
	float elapsedTime;
	MoveInfo deltaMove;
	int hp;
	
public:
	GameObject() :pos({ 0,0 }), angle(0), speed(0), period(0), amplitude(0), collider(Collider()), elapsedTime(0), hp(0) {}
	virtual ~GameObject() {}

	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void Release() {}
	virtual void Render(HDC hdc) {}

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetElapsedTime(float elapsedTime) { this->elapsedTime = elapsedTime; }
	inline POINTFLOAT GetPos() { return { pos.x + deltaMove.deltaPos.x, pos.y + deltaMove.deltaPos.y }; }
};