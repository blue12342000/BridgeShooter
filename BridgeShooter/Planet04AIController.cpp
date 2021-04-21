#include "Planet04AIcontroller.h"
#include "Unit.h"
#include "Pattern.h"
#include "BasicPattern.h"

void Planet04AIcontroller::Init()
{
	
	vLpPatterns.resize((int)USE_PATTERN::NONE);
	vLpPatterns[(int)USE_PATTERN::BASIC] = new BasicPattern();
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
			if (lpUnit->pos.x < 50 || lpUnit->pos.y < 50
				|| lpUnit->pos.x > WINSIZE_WIDTH - 50 || lpUnit->pos.y > WINSIZE_HEIGHT / 2 - 50)
			{lpUnit->ResetTimer();
				state = UNIT_STATE::RETURN;
			}
			else
			{
				if (rand() % 2 == 0)
				{
					lpUnit->ResetTimer();
					lpUnit->elapsedTime = elapsedTime;
					elapsedTime = 0;
					state = UNIT_STATE::ATTACK;
				}
				else
					state = UNIT_STATE::MOVE;
			}
			break;
		case UNIT_STATE::MOVE:
			lpUnit->transform.speed = 400;
			lpUnit->Translate(POINTFLOAT{ (float)((rand() % 150 + 60) - 135) / 10, (float)((rand() % 150 + 60) - 135) / 10 });
			state = UNIT_STATE::MOVE_PATTERN;//MOVE_ING;
			elapsedTime = 0;
			break;

		/*case UNIT_STATE::MOVE_ING:
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
			break;*/
		case UNIT_STATE::MOVE_PATTERN:
			elapsedTime = 8;
			lpUnit->ResetTimer();
			lpUnit->lpPattern = vLpPatterns[(int)currentPattern];
			lpUnit->transform.speed = 100;
			state = UNIT_STATE::MOVE_PATTERN_ING;
			break;
		case UNIT_STATE::MOVE_PATTERN_ING:
			if (elapsedTime > 3)
			{
				elapsedTime = 0;
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::ATTACK:
			currentPattern = USE_PATTERN::NONE;
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
			elapsedTime++;
			if (elapsedTime > 10000)
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
			}
		}
}

void Planet04AIcontroller::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}

void Planet04AIcontroller::SetUnit(Unit* lpUnit)
{
	this->isReady = false;
	this->lpUnit = lpUnit;
	this->lpUnit->Init();
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetUnitKind(UNIT_KIND::BOSS);
	this->lpUnit->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };
}