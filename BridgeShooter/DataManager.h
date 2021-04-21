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
		NONE
	};

private:
	int selectedCharacter;
	float playTime;

	int bombAmount;
	int lifeAmount;


public:
	HRESULT Init();
	void Update(float deltaTime);
	inline void SetCharacter(CHARACTER_CODE characterCode) { this->selectedCharacter = (int)characterCode; }
	inline int GetSelectedCharacter() { return selectedCharacter; }
	inline void SetPlayTime(float playTime) { this->playTime = playTime; }
	inline float GetPlayTime() { return this->playTime; }
	inline void SetBombAmount(int bombAmount) { this->bombAmount = bombAmount; }
	inline int GetBombAmount() { return this->bombAmount; }
	inline int GetLifeAmount() { return this->lifeAmount; }
};

