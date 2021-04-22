#include "SSJAIController.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SSJFactory.h"

void SSJAIController::Init()
{
	vLpPatterns.resize((int)USE_PATTERN::NONE);
	vLpPatterns[(int)USE_PATTERN::BASIC] = new BasicPattern();
	state = UNIT_STATE::RETURN;
	currentPattern = USE_PATTERN::NONE;
	elapsedTime = 0;
	distance = 0;
}

void SSJAIController::Release()
{
	if (lpUnit)
	{
		lpUnit->Release();
		delete lpUnit;
		lpUnit = nullptr;
	}

	for (auto lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void SSJAIController::Update(float deltaTime)
{
	if (lpUnit)
	{
		switch (state)
		{
		case UNIT_STATE::IDLE:
			currentPattern = USE_PATTERN::NONE;
			if (lpUnit->pos.y < 0)
			{
				state = UNIT_STATE::RETURN;
			}
			else
			{
				state = UNIT_STATE::ATTACK;
			}
			break;
		case UNIT_STATE::ATTACK:
			currentPattern = USE_PATTERN::NONE;
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
			elapsedTime++;
			if (elapsedTime>10000) 
			{
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			currentPattern = USE_PATTERN::BASIC;
			vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			lpUnit->Fire();			
			lpUnit->Update(deltaTime);
			if (lpUnit->pos.x > 500)
			{
				lpUnit->angle = PI;
				lpUnit->Translate(POINTFLOAT{ -10, 0 });
			}
			else if (lpUnit->pos.x < 100)
			{
				lpUnit->angle = 0;
			}
			break;
		case UNIT_STATE::RETURN:
			if (lpUnit->pos.y < 200)
			{
				lpUnit->pos.y += 0.3f;
				lpUnit->Translate(POINTFLOAT{ 0, -1 });
			}
			else if (lpUnit->pos.y >= 200)
			{
				elapsedTime = 0;
				state = UNIT_STATE::ATTACK;
			}
			break;
		case UNIT_STATE::NONE:
			break; 
		}
	}
}

void SSJAIController::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}

void SSJAIController::SetUnit(Unit* lpUnit)
{
	this->isReady = false;
	this->lpUnit = lpUnit;
	this->lpUnit->Init();
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetUnitKind(UNIT_KIND::BOSS);
	this->lpUnit->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };
}