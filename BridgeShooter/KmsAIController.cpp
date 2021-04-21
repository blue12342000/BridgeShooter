#include "KmsAIController.h"
#include "Unit.h"
#include "Pattern.h"
#include "ReflectPattern.h"
#include "Planet_KMS_Factory.h"
#include "ReflectPattern.h"


void KmsAIController::Init()
{
	elapsedTime = 0;
	prevNum = 0;
	lpPattern = new ReflectPattern();
}

void KmsAIController::Release()
{
	if (lpUnit) 
	{
		lpUnit->Release();
		delete lpUnit;
		lpUnit = nullptr;
	}
	if (lpPattern) 
	{
		delete lpPattern;
		lpPattern = nullptr;
	}
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
			lpUnit->SetElapsedTime(2);//계속 팅기게(10보다 작게)
			if (lpUnit->GetHp() >= 300)
			{
				prevNum = 0;
				lpUnit->transform.speed = 0;
				lpUnit->SetFactoryLine(0);
			}
			else if (lpUnit->GetHp() >= 100)
			{
				if (prevNum != 1) 
				{
					lpUnit->angle = 0;
				}
				prevNum = 1;
				lpUnit->transform.speed = 100;
				lpUnit->SetFactoryLine(1);

			}
			else
			{
				if (prevNum != 2)
				{
					lpUnit->angle = PI*2/3;
				}
				prevNum = 2;
				lpUnit->transform.speed = rand()%200+100;
				lpUnit->SetFactoryLine(2);
			}
			if (lpPattern)
			{
				lpPattern->Move(deltaTime, lpUnit);
			}
			lpUnit->Fire();
			lpUnit->Update(deltaTime);
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