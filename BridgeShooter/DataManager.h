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
	CHARACTER_CODE selectedCharacter;
	float playTime;

public:
	HRESULT Init();
	void Update(float deltaTime);
	inline void SetCharacter(CHARACTER_CODE characterCode) { this->selectedCharacter = characterCode; }
	inline CHARACTER_CODE GetSelectedCharacter() { return this->selectedCharacter; }
	inline void SetPlayTime(float playTime) { this->playTime = playTime; }
	inline float GetPlayTime() { return this->playTime; }
};

