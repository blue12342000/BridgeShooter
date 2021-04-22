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
			lpObject->originAngle : 첫 진동의 방향
			lpObject->speed : 직선으로 쐈을때 속도
			lpObject->period : 사인곡선의 주기 이 값이 커질수록 1초에 많이 진동한다
			lpObject->amplitude : 사인곡선의 진폭 클수록 진동의 깊이가 커진다
			lpObject->pos : 실제 위치
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

	
