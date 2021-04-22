#include "Planet04AIcontroller.h"
#include "Unit.h"
#include "Pattern.h"
#include "BasicPattern.h"
#include "RainPattern.h"


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
					elapsedTime = 0;
					state = UNIT_STATE::MOVE;
			}
			break;

		case UNIT_STATE::MOVE:
			if (rand()% 10 < 4)
			{
				lpUnit->pos.x -= 200.0f;
				lpUnit->pos.y -= 200.0f;
			}
			else
			{
				lpUnit->pos.x += 200.0f;
				lpUnit->pos.y += 200.0f;
			}
			elapsedTime = 0;
			state = UNIT_STATE::ATTACK;
			break;
		case UNIT_STATE::ATTACK:
			currentPattern = USE_PATTERN::NONE;
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
			elapsedTime++;
			if (elapsedTime > 100)
			{
				state = UNIT_STATE::PATTERN_ATTACK;
			}
			break;
		case UNIT_STATE::PATTERN_ATTACK:
			currentPattern = USE_PATTERN::BASIC;
			lpUnit->ChangeFactoryLine(1);
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
			break;
		case UNIT_STATE::RETURN:
			if (lpUnit->pos.y < 200)
			{
				lpUnit->pos.y += 15.0f;
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