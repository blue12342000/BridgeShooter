#pragma once
#include <map>

class Unit;
class Factory
{
private:
	struct TimeCheck
	{
		float nextTime;
		bool isChanged;
	};

private:
	float elapsedTime;
	std::map<int, TimeCheck> mTimeCheck;

protected:
	int createLine;
	int maxCreateLIne;

public:
	Factory():createLine(0), maxCreateLIne(0), elapsedTime(0) {}
	virtual ~Factory() {}

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float deltaTime) final;
	virtual void Fire(Unit* lpUnit) = 0;

	virtual void ResetTimer() final;

	inline int SetCreateLine(int createLine) { (maxCreateLIne > 0 && createLine > 0) ? this->createLine = createLine % maxCreateLIne : this->createLine = 0; return this->createLine; }
	inline void SetCheckTime(int millisec) { mTimeCheck.insert(std::make_pair(millisec, TimeCheck{ (float)millisec/1000.0f, false})); }
	inline bool IsCheckTime(int millisec) { return mTimeCheck[millisec].isChanged; }
	inline int GetTimeMod(int millisec) { return ((int)(elapsedTime * 1000)) % millisec; }
	inline int GetMaxCreateLIne() { return maxCreateLIne; }

};