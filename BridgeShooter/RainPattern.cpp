#include "RainPattern.h"
#include "GameObject.h"
#include "Planet04.h"

MoveInfo RainPattern::Move(float deltaTime, GameObject* lpObject)
{
	//���ߴ��� : ź���� ���ϴ� ��ġ�� �Ѹ��� 6�ʰ� ������Ű�� �� ��ġ���� �ҳ���ó����������ϱ�
	//���� �Ǵ°� : ������ ��ġ�� �Ѹ���(������Ʈ�� �߽�) ������Ű�� 6���� ������ �߻�
	MoveInfo moveInfo = {0, 0};
	if (lpObject)
	{
		//�������� �󸶳� ������ ���ߴ���
		if (lpObject->elapsedTime < 4.5f)
		{
			moveInfo.angle = lpObject->angle;
			lpObject->pos.x -= cosf(lpObject->angle) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4;
			lpObject->pos.y -= sinf(lpObject->angle) * lpObject->speed * deltaTime * lpObject->elapsedTime / 4; // elapsedTime �� ����. delltaTime�� ������ �ƴ�.
		}

		if (lpObject->elapsedTime > 4.5f)
		{
			//������ �ڵ�� �����ϰ� ���� SetPattern���� �����Ұ�
			lpObject->angle = PI / 2;
			moveInfo.angle = lpObject->angle;
			lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime / 3;
			lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime / 3;
		}

	}
	return moveInfo;
}
