#include "DataManager.h"

HRESULT DataManager::Init()
{
	selectedCharacter = (int)CHARACTER_CODE::NONE;
	playTime = 0.0f;
	lifeAmount = 3;
	return S_OK;
}

void DataManager::Update(float deltaTime)
{
	playTime += deltaTime;
}
