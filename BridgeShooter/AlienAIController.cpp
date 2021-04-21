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

void AlienAIController::SetUnit(Unit* lpUnit)
{
	this->isReady = false;
	this->lpUnit = lpUnit;
	this->lpUnit->Init();
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetUnitKind(UNIT_KIND::ENEMY);
	this->lpUnit->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };
}
