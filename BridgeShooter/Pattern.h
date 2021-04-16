#pragma once

class GameObject; 
class Pattern
{
private:
	float elapsedTime;

public:
	Pattern() {};
	virtual ~Pattern() {};

	virtual void Move(float deltaTime, GameObject* lpObject);
};

