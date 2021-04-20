#include "AlienAIController.h"

#include "Unit.h"
#include "Pattern.h"


void AlienAIController::Init()
{
	
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
		if (lpUnit->hp <= 0)
		{

		}
		else 
		{
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
		}
	}
	elapsedTime += deltaTime;
}

void AlienAIController::Render(HDC hdc)
{
	if (lpUnit)
	{
		lpUnit->Render(hdc);
	}
}
