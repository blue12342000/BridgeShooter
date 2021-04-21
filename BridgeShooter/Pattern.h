#pragma once

struct MoveInfo;
class GameObject;
class Pattern
{
public:
	Pattern() {};
	virtual ~Pattern() {};

	virtual void Move(float deltaTime, GameObject* lpObject) = 0;
};

