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
	lpUnit->transform.speed = 100;
	goalPos = { WINSIZE_WIDTH / 2.0f,200.0f };
	prevNum = U_MAX_BOSS_HP;
	state = UNIT_STATE::RETURN;
	currentPattern = USE_PATTERN::REFLECT;
}

void KmsAIController::Release()
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

void KmsAIController::Update(float deltaTime)
{
	if (lpUnit)
	{
		if (lpUnit->GetHp() <= 0) 
		{

		}
		else
		{
			if ((prevNum - 800) >= lpUnit->GetHp())
			{
				state = UNIT_STATE::UPGRADE;
				lpUnit->transform.speed += 100;
				prevNum = lpUnit->GetHp();
			}
			
		}
		
		switch (state)
		{

		case UNIT_STATE::IDLE:
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
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
			elapsedTime+= deltaTime;
			if (elapsedTime>5) 
			{
				lpUnit->angle = (rand() % ((int)(2 * PI * 1000))) / 1000;
				state = UNIT_STATE::MOVE;
				elapsedTime = 0;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			lpUnit->Fire();			
			lpUnit->Update(deltaTime);
			elapsedTime += deltaTime;
			if ((lpUnit->pos.y < 0) || (lpUnit->pos.y > WINSIZE_HEIGHT / 2) || (lpUnit->pos.x < 0) || (lpUnit->pos.x > WINSIZE_WIDTH))
			{
				state = UNIT_STATE::RETURN;
			}
			if (elapsedTime > 5)
			{
				lpUnit->angle = (rand() % ((int)(2 * PI * 1000))) / 1000;
				state = UNIT_STATE::MOVE;
				elapsedTime = 0;
			}
			break;
		case UNIT_STATE::RETURN:
			goalPos = { (float)(rand() % WINSIZE_WIDTH),(float)((rand() % ((WINSIZE_HEIGHT / 2)  + 1)) )};
			lpUnit->angle = atan2((goalPos.y - lpUnit->pos.y), (goalPos.x - lpUnit->pos.x));
			vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			if (sqrt((goalPos.y - lpUnit->pos.y) * (goalPos.y - lpUnit->pos.y) + (goalPos.x - lpUnit->pos.x) * (goalPos.x - lpUnit->pos.x)) <= 50)
			{
				state = UNIT_STATE::ATTACK;
			}
			
			break;
		case UNIT_STATE::MOVE:
			vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			lpUnit->Update(deltaTime);
			elapsedTime += deltaTime;
			if ((lpUnit->pos.y < 0) || (lpUnit->pos.y > WINSIZE_HEIGHT / 2) || (lpUnit->pos.x < 0) || (lpUnit->pos.x > WINSIZE_WIDTH))
			{
				state = UNIT_STATE::RETURN;
			}
			if (elapsedTime>5)
			{
				if (rand() % 2) 
				{
					state = UNIT_STATE::ATTACK;
					elapsedTime = 0;
				}
				else 
				{
					lpUnit->angle = (rand() % ((int)(2 * PI * 1000))) / 1000;
					state = UNIT_STATE::PATTERN_ATTACK;
					elapsedTime = 0;
				}
				
			}
			break;
		case UNIT_STATE::UPGRADE:
			lpUnit->ChangeFactoryLine(1);
			state = UNIT_STATE::IDLE;
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

void KmsAIController::SetUnit(Unit* lpUnit)
{
	this->isReady = false;
	this->lpUnit = lpUnit;
	this->lpUnit->Init();
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetUnitKind(UNIT_KIND::BOSS);
	this->lpUnit->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };
}