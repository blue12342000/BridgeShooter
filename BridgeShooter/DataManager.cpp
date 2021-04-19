#include "DataManager.h"

HRESULT DataManager::Init()
{
	selectedCharacter = CHARACTER_CODE::NONE;
	playTime = 0.0f;
	return S_OK;
}

void DataManager::Update(float deltaTime)
{
	playTime += deltaTime;
}
