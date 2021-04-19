#include "DataManager.h"

HRESULT DataManager::Init()
{
	selectedCharacter = (int)CHARACTER_CODE::NONE;
	playTime = 0.0f;
	return S_OK;
}

void DataManager::Update(float deltaTime)
{
	playTime += deltaTime;
}
