#include "RainPattern.h"
#include "GameObject.h"
#include "Planet04.h"

void RainPattern::Move(float deltaTime, GameObject* lpObject)
{
	//���ߴ��� : ź���� ���ϴ� ��ġ�� �Ѹ��� 6�ʰ� ������Ű�� �� ��ġ���� �ҳ���ó����������ϱ�
	//���� �Ǵ°� : ������ ��ġ�� �Ѹ���(������Ʈ�� �߽�) ������Ű�� 6���� ������ �߻�

	if (lpObject)
	{
		Transform& transform = lpObject->transform;
		//�������� �󸶳� ������ ���ߴ���
		if (lpObject->elapsedTime < 4.5f)
		{
			lpObject->pos.x -= cosf(lpObject->angle) * transform.speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y -= sinf(lpObject->angle) * transform.speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime �� ����. delltaTime�� ������ �ƴ�.
		}

		if (lpObject->elapsedTime > 4.5f)
		{
			lpObject->angle = PI / 2;
			
			lpObject->pos.x += cos(lpObject->angle) * transform.speed * deltaTime / 3;
			lpObject->pos.y += sin(lpObject->angle) * transform.speed * deltaTime / 3;
		}

	}
}
