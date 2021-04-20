#include "Planet04AIcontroller.h"
#include "Unit.h"
#include "Pattern.h"
#include "BasicPattern.h"
#include "CircleMovePattern.h"

void Planet04AIcontroller::Init()
{
	vLpPatterns.resize((int)USE_PATTERN::NONE);
	vLpPatterns[(int)USE_PATTERN::BASIC] = new BasicPattern();
	vLpPatterns[(int)USE_PATTERN::CIRCLE] = new CircleMovePattern();
	state = UNIT_STATE::IDLE;
	currentPattern = USE_PATTERN::NONE;
	elapsedTime = 0;
}

void Planet04AIcontroller::Release()
{
	for (auto lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void Planet04AIcontroller::Update(float deltaTime)
{
	if (lpUnit)
	{
		switch (state)
		{
		case UNIT_STATE::IDLE:
			currentPattern = USE_PATTERN::NONE;
			if (rand() % 100 < 30)
			{
				elapsedTime = 0;
				lpUnit->SetElapsedTime(elapsedTime);
				state = UNIT_STATE::ATTACK;
			}
			else
			{
				if (rand() % 10 < 5)
				{
					elapsedTime = 0;
					lpUnit->SetElapsedTime(elapsedTime);
					state = UNIT_STATE::MOVE;
				}
				else
				{
					elapsedTime = 0;
					lpUnit->SetElapsedTime(elapsedTime);
					currentPattern = (USE_PATTERN)(rand() % vLpPatterns.size());
					state = UNIT_STATE::MOVE_PATTERN;
				}
			}
			break;
		case UNIT_STATE::MOVE:
			if (elapsedTime < 4)
			{
				if (lpUnit->pos.x < 100 || lpUnit->pos.y < 100
					|| lpUnit->pos.x > WINSIZE_WIDTH - 100 || lpUnit->pos.y > WINSIZE_HEIGHT - 100)
				{
					float angle = atan2(origin.y - lpUnit->pos.y, origin.x - lpUnit->pos.x);
					lpUnit->Translate(POINTFLOAT{ cosf(angle) * 10, sin(angle) * 10 });
				}
				else
				{
					lpUnit->Translate(POINTFLOAT{ (float)(rand() % 70 - 30) / 10, (float)(rand() % 70 - 30) / 10 });
				}
			}
			else
			{
				if (rand() % 10 < 3)
				{
					state = UNIT_STATE::RETURN;
				}
				else
				{
					elapsedTime = 0;
					lpUnit->SetElapsedTime(elapsedTime);
					state = UNIT_STATE::ATTACK;
				}
			}
			break;
		case UNIT_STATE::MOVE_PATTERN:
			lpUnit->deltaMove = vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			if (elapsedTime > 3)
			{
				elapsedTime = 0;
				lpUnit->SetElapsedTime(elapsedTime);
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			lpUnit->deltaMove = vLpPatterns[(int)currentPattern]->Move(deltaTime, lpUnit);
			if (elapsedTime < 10)
			{
				lpUnit->Fire();
			}
			else
			{
				state = UNIT_STATE::UPGRADE;
			}
			break;
		case UNIT_STATE::ATTACK:
			if (elapsedTime < 10)
			{
				lpUnit->Fire();
			}
			else
			{
				state = UNIT_STATE::UPGRADE;
			}
			break;
		case UNIT_STATE::UPGRADE:
			lpUnit->ChangeFactoryLine(1);
			state = UNIT_STATE::RETURN;
			break;
		case UNIT_STATE::RETURN:
			float distance = pow(origin.y - lpUnit->pos.y, 2) + pow(origin.x - lpUnit->pos.x, 2);
			if (distance > 100)
			{
				float angle = atan2(origin.y - lpUnit->pos.y, origin.x - lpUnit->pos.x);
				lpUnit->Translate(POINTFLOAT{ cosf(angle) * 10, sin(angle) * 10 });
			}
			if (distance < 10)
			{
				lpUnit->SetPos(origin);
				state = UNIT_STATE::IDLE;
			}
			break;
		}


		lpUnit->Update(deltaTime);
	}
	elapsedTime += deltaTime;
}

void Planet04AIcontroller::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}
