#include "SinePattern.h"
#include "GameObject.h"

void SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	if (lpObject)
	{
		//사인처럼 움직이게 각도값을 계속 변경...할수가있나? 값 계산 방법 고민
		//sin 미분 -> cos , cos 미분 -> -sin 인걸로 1차함수 그래프 만들어봄
		float deltaAngleX = -1 * sinf(lpObject->angle) * lpObject->elapsedTime;	//이거 자체를 다시 asinf로 각도로 변환해야하는가?
		float deltaAngleY = cosf(lpObject->angle) * lpObject->elapsedTime;

		lpObject->pos.x = lpObject->speed * deltaTime * cos(lpObject->angle + deltaAngleX);
		lpObject->pos.y = lpObject->speed * deltaTime * sin(lpObject->angle + deltaAngleY);

	}

}
