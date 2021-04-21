#include "JinHwangAIContoller.h"
#include "Unit.h"
#include "Pattern.h"
#include "BasicPattern.h"

void JinHwangAIContoller::Init()
{
	state = UNIT_STATE::IDLE;
	elapsedTime = 0;

	origin = { WINSIZE_WIDTH / 2.0f, WINSIZE_HEIGHT / 4.0f };
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
			if (lpUnit->pos.x < 50 || lpUnit->pos.y < 50
				|| lpUnit->pos.x > WINSIZE_WIDTH - 50 || lpUnit->pos.y > WINSIZE_HEIGHT / 2 - 50)
			{
				state = UNIT_STATE::MOVE;
			}
			else
			{
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
						state = UNIT_STATE::MOVE;
					}
				}
			}
			break;
		case UNIT_STATE::MOVE:
			if (lpUnit->pos.x < 50 || lpUnit->pos.y < 50
				|| lpUnit->pos.x > WINSIZE_WIDTH - 50 || lpUnit->pos.y > WINSIZE_HEIGHT / 2 - 50)
			{
				lpUnit->Translate(POINTFLOAT{ origin.x - lpUnit->pos.x, origin.y - lpUnit->pos.y });
				state = UNIT_STATE::MOVE;
			}
			else
			{
				lpUnit->Translate(POINTFLOAT{ (float)((rand() % 150 + 60) - 135) / 10, (float)((rand() % 150 + 60) - 135) / 10 });
				state = UNIT_STATE::MOVE_ING;
				elapsedTime = 0;
			}
			break;
		case UNIT_STATE::MOVE_ING:
			if (elapsedTime > 2)
			{
				if (lpUnit->pos.x < 50 || lpUnit->pos.y < 50
					|| lpUnit->pos.x > WINSIZE_WIDTH - 50 || lpUnit->pos.y > WINSIZE_HEIGHT / 2 - 50)
				{
					lpUnit->Translate(POINTFLOAT{ origin.x - lpUnit->pos.x, origin.y - lpUnit->pos.y });
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
				lpUnit->Translate(POINTFLOAT{ origin.x - lpUnit->pos.x, origin.y - lpUnit->pos.y });
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

void JinHwangAIContoller::SetUnit(Unit* lpUnit)
{
	this->isReady = false;
	this->lpUnit = lpUnit;
	this->lpUnit->Init();
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetUnitKind(UNIT_KIND::BOSS);
	this->lpUnit->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT / 4 - 300 };
}