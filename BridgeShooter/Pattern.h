#pragma once

struct MoveInfo;
class GameObject;
class Pattern
{
public:
	Pattern() {};
	virtual ~Pattern() {};

	virtual MoveInfo Move(float deltaTime, GameObject* lpObject) = 0;
};

