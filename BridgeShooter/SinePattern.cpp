#include "SinePattern.h"
#include "GameObject.h"

MoveInfo SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo = { 0, 0 };
	if (lpObject)
	{
		/*
			lpObject->originAngle : 첫 진동의 방향
			lpObject->speed : 직선으로 쐈을때 속도
			lpObject->period : 사인곡선의 주기 이 값이 커질수록 1초에 많이 진동한다
			lpObject->amplitude : 사인곡선의 진폭 클수록 진동의 깊이가 커진다
			lpObject->pos : 실제 위치

			
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
