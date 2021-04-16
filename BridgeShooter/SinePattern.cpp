#include "SinePattern.h"
#include "GameObject.h"

void SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	float deltaAngle = 0;	//����ó�� �����̰� �������� ��� ����...�Ҽ����ֳ�?

	lpObject->pos.x = lpObject->speed * deltaTime * cos(lpObject->angle + deltaAngle);  
	lpObject->pos.y = lpObject->speed * deltaTime * sin(lpObject->angle + deltaAngle); 
	
}
