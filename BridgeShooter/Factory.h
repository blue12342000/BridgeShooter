#pragma once
class Unit;
class Factory
{
protected:
	int createLine;
	int maxCreateLIne;

public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Fire(Unit* lpUnit) = 0;
	virtual inline void SetCreateLine(int createLine) final { (maxCreateLIne > 0) ? this->createLine = createLine % maxCreateLIne : this->createLine = 0; }
};