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
		if ((lpUnit->hp > 0) && ((lpUnit->pos.x > WINSIZE_LEFT) && (lpUnit->pos.x < WINSIZE_RIGHT) &&
			(lpUnit->pos.y > WINSIZE_TOP) && (lpUnit->pos.y < WINSIZE_BOTTOM)))
		{
			lpUnit->Update(deltaTime);
		}
		else
		{
			if ((rand() % 1000000) <= 100)
			{
				lpUnit->hp = 100;
				lpUnit->SetPos({ WINSIZE_WIDTH / 2.0f,WINSIZE_HEIGHT / 2.0f });
			}
		}
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
