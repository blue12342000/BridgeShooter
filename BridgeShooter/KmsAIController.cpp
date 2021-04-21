#include "KmsAIController.h"
#include "Unit.h"
#include "Pattern.h"
#include "ReflectPattern.h"
#include "Planet_KMS_Factory.h"
#include "ReflectPattern.h"


void KmsAIController::Init()
{
	vLpPatterns.resize((int)USE_PATTERN::NONE);
	vLpPatterns[(int)USE_PATTERN::REFLECT] = new ReflectPattern();
	elapsedTime = 0;
	prevNum = 500;
	state = UNIT_STATE::RETURN;
}

void KmsAIController::Release()
{
	
	for (auto lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void KmsAIController::Update(float deltaTime)
{
	if (lpUnit)
	{
		if (lpUnit->hp <= 0)
		{

		}
		else
		{
			if ((prevNum - 200) >= lpUnit->hp)
			{
				state = UNIT_STATE::UPGRADE;
				lpUnit->speed += 100;
				prevNum = lpUnit->hp;
			}
			
		}
		
		switch (state)
		{

		case UNIT_STATE::IDLE:
			currentPattern = USE_PATTERN::NONE;
			if ((lpUnit->pos.y < 0)|| (lpUnit->pos.y > WINSIZE_HEIGHT/2)|| (lpUnit->pos.x < 0)|| (lpUnit->pos.x > WINSIZE_WIDTH))
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
			elapsedTime+= deltaTime;
			if (elapsedTime>20) 
			{
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			currentPattern = USE_PATTERN::REFLECT;
			lpUnit->deltaMove = vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			lpUnit->Fire();			
			lpUnit->Update(deltaTime);
			if ((lpUnit->pos.y < 0) || (lpUnit->pos.y > WINSIZE_HEIGHT / 2) || (lpUnit->pos.x < 0) || (lpUnit->pos.x > WINSIZE_WIDTH))
			{
				state = UNIT_STATE::RETURN;
			}
			break;
		case UNIT_STATE::RETURN:
			if (lpUnit->pos.x < 0)
			{
				lpUnit->angle = 0;
			}
			else if (lpUnit->pos.x > WINSIZE_WIDTH)
			{
				lpUnit->angle = PI;
			}
			if (lpUnit->pos.y <0)
			{
				lpUnit->angle = PI/2;
			}
			else if (lpUnit->pos.y >WINSIZE_HEIGHT / 2)
			{
				lpUnit->angle = -PI/2;
			}
			state = UNIT_STATE::MOVE;
			break;
		case UNIT_STATE::MOVE:
			lpUnit->deltaMove = vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			lpUnit->Update(deltaTime);
			if ((lpUnit->pos.y < 0) || (lpUnit->pos.y > WINSIZE_HEIGHT / 2) || (lpUnit->pos.x < 0) || (lpUnit->pos.x > WINSIZE_WIDTH))
			{
				state = UNIT_STATE::RETURN;
			}
			break;
		case UNIT_STATE::UPGRADE:
			lpUnit->ChangeFactoryLine(1);
			state = UNIT_STATE::RETURN;
			break;
		case UNIT_STATE::NONE:
			break; 
		}
	}
	elapsedTime += deltaTime;
}


void KmsAIController::Render(HDC hdc)
{
	if (lpUnit)
	{
		lpUnit->Render(hdc);
	}
}