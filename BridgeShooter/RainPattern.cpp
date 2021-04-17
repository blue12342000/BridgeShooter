#include "RainPattern.h"
#include "GameObject.h"
#include "Planet.h"


MoveInfo RainPattern::Move(float deltaTime, GameObject* lpObject)
{
	//���ߴ��� : ź���� ���ϴ� ��ġ�� �Ѹ��� 6�ʰ� ������Ű�� �� ��ġ���� �ҳ���ó����������ϱ�
	//���� �Ǵ°� : ������ ��ġ�� �Ѹ���(������Ʈ�� �߽�) ������Ű�� 6���� ������ �߻�
	MoveInfo moveInfo = {0, 0};
	if (lpObject)
	{
		float count = lpObject->elapsedTime;

		//�������� �󸶳� ������ ���ߴ���
		if (lpObject->elapsedTime< 0.1f)
		{
			lpObject->pos.x -= cosf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y -= sinf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime �� ����. delltaTime�� ������ �ƴ�.
		}
		//���������� �󸶳� ������ ���ߴ���
		/*
		if (lpObject->elapsedTime < 0.1f)
		{
			lpObject->pos.x += cosf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y += sinf(lpObject->angle * elapsedTime) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime �� ����. delltaTime�� ������ �ƴ�.
		}
		*/
		//6�� �ִٰ� deltaTime * �� ��ŭ �ӵ��� ���ؼ� �����ɴ´�
		/*
		if (lpObject->elapsedTime > 6.0f)
		{
			lpObject->pos.x -= cos(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
			lpObject->pos.y -= sin(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
		}
		*/
		//6�� �ִٰ� deltaTime * �� ��ŭ �ӵ��� ���ؼ� �������� �ɴ´�
		if (lpObject->elapsedTime > 6.0f)
		{
			lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
			lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime * 30.0f;
		}

	}
	
	return moveInfo;
}
