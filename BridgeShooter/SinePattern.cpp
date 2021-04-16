#include "SinePattern.h"
#include "GameObject.h"

void SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	float deltaAngle = 0;	//사인처럼 움직이게 각도값을 계속 변경...할수가있나?

	lpObject->pos.x = lpObject->speed * deltaTime * cos(lpObject->angle + deltaAngle);  
	lpObject->pos.y = lpObject->speed * deltaTime * sin(lpObject->angle + deltaAngle); 
	
}
