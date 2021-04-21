#include "SinePattern.h"
#include "GameObject.h"

MoveInfo SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo = { 0, 0 };
	if (lpObject)
	{
		/*
			lpObject->originAngle : ù ������ ����
			lpObject->speed : �������� ������ �ӵ�
			lpObject->period : ���ΰ�� �ֱ� �� ���� Ŀ������ 1�ʿ� ���� �����Ѵ�
			lpObject->amplitude : ���ΰ�� ���� Ŭ���� ������ ���̰� Ŀ����
			lpObject->pos : ���� ��ġ

			
		*/
		float ratio = lpObject->elapsedTime;
		if (ratio > 1) ratio /= ratio;
		lpObject->pos.x = lpObject->origin.x + cosf(lpObject->angle) * lpObject->speed * lpObject->elapsedTime
			+ cosf(lpObject->angle + lpObject->originAngle) * sin(lpObject->originAngle) * ratio * sin(lpObject->angle + lpObject->originAngle + lpObject->period * lpObject->elapsedTime) * lpObject->amplitude;
		lpObject->pos.y = lpObject->origin.y + sinf(lpObject->angle) * lpObject->speed * lpObject->elapsedTime
			+ sinf(lpObject->angle + lpObject->originAngle) * sin(lpObject->originAngle) * ratio * sin(lpObject->angle + lpObject->originAngle + lpObject->period * lpObject->elapsedTime) * lpObject->amplitude;
	}
	return moveInfo;
}
