#pragma once

class GameObject; 
class Pattern
{
protected:
	float elapsedTime;

public:
	Pattern():elapsedTime(0) {};
	virtual ~Pattern() {};

	virtual void Move(float deltaTime, GameObject* lpObject) = 0;
};

