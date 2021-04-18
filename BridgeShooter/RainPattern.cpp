#include "RainPattern.h"
#include "GameObject.h"
#include "Planet04.h"

MoveInfo RainPattern::Move(float deltaTime, GameObject* lpObject)
{
	//원했던것 : 탄막을 원하는 위치에 뿌리고 6초간 정지시키고 각 위치에서 소나기처럼쏟아지게하기
	//현재 되는것 : 지정된 위치에 뿌리고(오브젝트의 중심) 고정시키고 6초후 빠르게 발사
	MoveInfo moveInfo = {0, 0};
	if (lpObject)
	{
		//왼쪽으로 얼마나 나가서 멈추느냐
		if (lpObject->elapsedTime < 4.5f)
		{
			moveInfo.angle = lpObject->angle;
			lpObject->pos.x -= cosf(lpObject->angle) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y -= sinf(lpObject->angle) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime 은 비율. delltaTime의 역할이 아님.
		}

		if (lpObject->elapsedTime > 4.5f)
		{
			//현세씨 코드랑 머지하고 나서 SetPattern으로 수정할것
			lpObject->angle = PI / 2;
			moveInfo.angle = lpObject->angle;
			lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime / 3;
			lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime / 3;
		}

	}
	return moveInfo;
}
