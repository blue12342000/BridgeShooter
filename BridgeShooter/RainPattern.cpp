#include "RainPattern.h"
#include "GameObject.h"
#include "Planet04.h"

void RainPattern::Move(float deltaTime, GameObject* lpObject)
{
	//원했던것 : 탄막을 원하는 위치에 뿌리고 6초간 정지시키고 각 위치에서 소나기처럼쏟아지게하기
	//현재 되는것 : 지정된 위치에 뿌리고(오브젝트의 중심) 고정시키고 6초후 빠르게 발사

	if (lpObject)
	{
		Transform& transform = lpObject->transform;
		//왼쪽으로 얼마나 나가서 멈추느냐
		if (lpObject->elapsedTime < 4.5f)
		{
			lpObject->pos.x -= cosf(transform.angle) * transform.speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y -= sinf(transform.angle) * transform.speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime 은 비율. delltaTime의 역할이 아님.
		}

		if (lpObject->elapsedTime > 4.5f)
		{
			transform.angle = PI / 2;
			
			lpObject->pos.x += cos(transform.angle) * transform.speed * deltaTime / 3;
			lpObject->pos.y += sin(transform.angle) * transform.speed * deltaTime / 3;
		}

	}
}
