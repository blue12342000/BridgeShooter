#pragma once
#include "Singleton.h"
#include <Windows.h>

class DataManager : public Singleton<DataManager>
{
public:
	enum class CHARACTER_CODE
	{
		YELLOW, 
		RED,
		GRAY,
		NONE,
		BOSS1,
		BOSS2,
		BOSS3,
		BOSS4
	};

private:
	int selectedCharacter;
	float playTime;

	int lifeAmount;


public:
	HRESULT Init();
	void Update(float deltaTime);
	inline void SetCharacter(CHARACTER_CODE characterCode) { this->selectedCharacter = (int)characterCode; }
	inline int GetSelectedCharacter() { return selectedCharacter; }
	inline void SetPlayTime(float playTime) { this->playTime = playTime; }
	inline float GetPlayTime() { return this->playTime; }
	inline int GetLifeAmount() { return this->lifeAmount; }
	inline void SetLifeAmount(int lifeAmount) { this->lifeAmount = lifeAmount; }
	inline bool UseLife() { if (lifeAmount > 0) { lifeAmount--; return true; } else { return false; } }
};

