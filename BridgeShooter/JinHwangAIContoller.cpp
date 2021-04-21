#include "JinHwangAIContoller.h"
#include "Unit.h"
#include "Pattern.h"
#include "BasicPattern.h"
#include "CircleMovePattern.h"

void JinHwangAIContoller::Init()
{
	vLpPatterns.resize((int)USE_PATTERN::NONE);
	vLpPatterns[(int)USE_PATTERN::BASIC] = new BasicPattern();
	vLpPatterns[(int)USE_PATTERN::CIRCLE] = new CircleMovePattern();
	state = UNIT_STATE::IDLE;
	currentPattern = USE_PATTERN::NONE;
	elapsedTime = 0;
}

void JinHwangAIContoller::Release()
{
	for (auto lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void JinHwangAIContoller::Update(float deltaTime)
{
	if (lpUnit)
	{
		switch (state)
		{
		case UNIT_STATE::IDLE:
			currentPattern = USE_PATTERN::NONE;
			if (elapsedTime > 1)
			{
				if (rand() % 100 < 10)
				{
					elapsedTime = 0;
					lpUnit->ResetTimer();
					state = UNIT_STATE::ATTACK;
				}
				else
				{
					elapsedTime = 0;
					//currentPattern = USE_PATTERN::CIRCLE;
					state = UNIT_STATE::MOVE;
				}
			}
			break;
		case UNIT_STATE::MOVE:
			lpUnit->transform.speed = 400;
			lpUnit->Translate(POINTFLOAT{ (float)((rand() % 150 + 60) - 135) / 10, (float)((rand() % 150 + 60) - 135) / 10 });
			state = UNIT_STATE::MOVE_ING;
			elapsedTime = 0;
			break;
		case UNIT_STATE::MOVE_ING:
			if (elapsedTime > 2)
			{
				if (lpUnit->pos.x < 50 || lpUnit->pos.y < 50
					|| lpUnit->pos.x > WINSIZE_WIDTH - 50 || lpUnit->pos.y > WINSIZE_HEIGHT / 2 - 50)
				{
					float angle = atan2(origin.y - lpUnit->pos.y, origin.x - lpUnit->pos.x);
					lpUnit->Translate(POINTFLOAT{ cosf(angle) * 10, sin(angle) * 10 });
					state = UNIT_STATE::MOVE_ING;
				}
				else
				{
					if (rand() % 100 < 30)
					{
						elapsedTime = 0;
						lpUnit->ResetTimer();
						state = UNIT_STATE::ATTACK;
					}
					else
					{
						state = UNIT_STATE::IDLE;
					}
				}
			}
			break;
		case UNIT_STATE::MOVE_PATTERN:
			elapsedTime = 0;
			lpUnit->ResetTimer();
			lpUnit->lpPattern = vLpPatterns[(int)currentPattern];
			lpUnit->transform.speed = 200;
			state = UNIT_STATE::MOVE_PATTERN_ING;
			break;
		case UNIT_STATE::MOVE_PATTERN_ING:
			if (elapsedTime > 3)
			{
				elapsedTime = 0;
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			if (elapsedTime < 10)
			{
				lpUnit->Fire();
			}
			else
			{
				lpUnit->lpPattern = nullptr;
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
				lpUnit->Translate(POINTFLOAT{cosf(angle) * 10, sin(angle) * 10});
			}
			if (distance < 100)
			{
				elapsedTime = 0;
				lpUnit->pos = origin;
				state = UNIT_STATE::IDLE;
			}
			break;
		}


		lpUnit->Update(deltaTime);
	}
	elapsedTime += deltaTime;
}

void JinHwangAIContoller::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}
