#pragma once

struct MoveInfo;
class GameObject;
class Pattern
{
protected:
	float elapsedTime;

public:
	Pattern():elapsedTime(0) {};
	virtual ~Pattern() {};

	virtual MoveInfo Move(float deltaTime, GameObject* lpObject) = 0;
};

