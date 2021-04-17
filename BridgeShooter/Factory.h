#pragma once
class Unit;
class Factory
{
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Fire(Unit* lpUnit) = 0;
};

