#include "AlienAIController.h"

#include "Unit.h"
#include "Pattern.h"


void AlienAIController::Init()
{
	lpUnit->Init();
}

void AlienAIController::Release()
{
	if (lpUnit)
	{
		lpUnit->Release();
		delete lpUnit;
		lpUnit = nullptr;
	}
}

void AlienAIController::Update(float deltaTime)
{
	if (lpUnit)
	{
		lpUnit->Update(deltaTime);
		elapsedTime += deltaTime;
	} 
}


void AlienAIController::Render(HDC hdc)
{
	if (lpUnit)
	{
		lpUnit->Render(hdc);
	}
}
