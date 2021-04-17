#include "RainPattern.h"
#include "GameObject.h"
#include "Planet.h"


MoveInfo RainPattern::Move(float deltaTime, GameObject* lpObject)
{
	//원했던것 : 탄막을 원하는 위치에 뿌리고 6초간 정지시키고 각 위치에서 소나기처럼쏟아지게하기
	//현재 되는것 : 지정된 위치에 뿌리고(오브젝트의 중심) 고정시키고 6초후 빠르게 발사
	MoveInfo moveInfo = {0, 0};
	if (lpObject)
	{
		float count = lpObject->elapsedTime;

		//왼쪽으로 얼마나 나가서 멈추느냐
		if (lpObject->elapsedTime< 0.1f)
		{
			lpObject->pos.x -= cosf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y -= sinf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime 은 비율. delltaTime의 역할이 아님.
		}
		//오른쪽으로 얼마나 나가서 멈추느냐
		/*
		if (lpObject->elapsedTime < 0.1f)
		{
			lpObject->pos.x += cosf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y += sinf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime 은 비율. delltaTime의 역할이 아님.
		}
		*/
		//6초 있다가 deltaTime * 값 만큼 속도를 곱해서 내려꽃는다
		/*
		if (lpObject->elapsedTime > 6.0f)
		{
			lpObject->pos.x -= cos(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
			lpObject->pos.y -= sin(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
		}
		*/
		//6초 있다가 deltaTime * 값 만큼 속도를 곱해서 위쪽으로 꽃는다
		if (lpObject->elapsedTime > 6.0f)
		{
			lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
			lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
		}

	}
	
	return moveInfo;
}
