#pragma once
class GameObject;
class Factory
{
public:
	virtual void Fire(GameObject* lpObject) = 0;
};

