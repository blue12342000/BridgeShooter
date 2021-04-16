#include "SinePattern.h"
#include "GameObject.h"

void SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	if (lpObject)
	{
		//����ó�� �����̰� �������� ��� ����...�Ҽ����ֳ�? �� ��� ��� ���
		//sin �̺� -> cos , cos �̺� -> -sin �ΰɷ� 1���Լ� �׷��� ����
		float deltaAngleX = -1 * sinf(lpObject->angle) * lpObject->elapsedTime;	//�̰� ��ü�� �ٽ� asinf�� ������ ��ȯ�ؾ��ϴ°�?
		float deltaAngleY = cosf(lpObject->angle) * lpObject->elapsedTime;

		lpObject->pos.x = lpObject->speed * deltaTime * cos(lpObject->angle + deltaAngleX);
		lpObject->pos.y = lpObject->speed * deltaTime * sin(lpObject->angle + deltaAngleY);

	}

}
