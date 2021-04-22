#include "SinePattern.h"
#include "GameObject.h"
#include "Missile.h"

void SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	if (lpObject)
	{
		if (typeid(*lpObject) == typeid(Missile))
		{
			Missile* lpMissile = (Missile*)lpObject;
			if (lpMissile->delayTime > 0.000001f)
			{
				lpMissile->delayTime -= deltaTime;
				return;
			}
		}

		/*
			lpObject->originAngle : ù ������ ����
			lpObject->speed : �������� ������ �ӵ�
			lpObject->period : ���ΰ�� �ֱ� �� ���� Ŀ������ 1�ʿ� ���� �����Ѵ�
			lpObject->amplitude : ���ΰ�� ���� Ŭ���� ������ ���̰� Ŀ����
			lpObject->pos : ���� ��ġ
		*/
		float ratio = lpObject->elapsedTime;
		if (ratio > 1) ratio /= ratio;
		Transform& transform = lpObject->transform;
		lpObject->pos.x = transform.pos.x + cosf(lpObject->angle) * transform.speed * lpObject->elapsedTime
			+ cosf(lpObject->angle + transform.angle) * sin(transform.angle) * ratio * sin(lpObject->angle + transform.angle + transform.period * lpObject->elapsedTime) * transform.amplitude;
		lpObject->pos.y = transform.pos.y + sinf(lpObject->angle) * transform.speed * lpObject->elapsedTime
			+ sinf(lpObject->angle + transform.angle) * sin(transform.angle) * ratio * sin(lpObject->angle + transform.angle + transform.period * lpObject->elapsedTime) * transform.amplitude;
	}
}

	
