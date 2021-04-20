#include "SSJAIController.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SSJFactory.h"

void SSJAIController::Init()
{
	vLpPatterns.resize((int)USE_PATTERN::NONE);
	vLpPatterns[(int)USE_PATTERN::BASIC] = new BasicPattern();
	state = UNIT_STATE::ATTACK;
	currentPattern = USE_PATTERN::NONE;
	elapsedTime = 0;
	
}

void SSJAIController::Release()
{
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
			state = UNIT_STATE::ATTACK;
			break;
		case UNIT_STATE::ATTACK:
			currentPattern = USE_PATTERN::NONE;
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
			elapsedTime++;
			if (elapsedTime>6500) 
			{
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			currentPattern = USE_PATTERN::BASIC;
			lpUnit->deltaMove = vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			lpUnit->Fire();			
			lpUnit->Update(deltaTime);
			if (lpUnit->pos.x > 600)
			{
				lpUnit->SetAngle(PI);
			}
			else if (lpUnit->pos.x < 100)
			{
				lpUnit->SetAngle(0);
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
