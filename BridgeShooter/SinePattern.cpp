#include "SinePattern.h"
#include "GameObject.h"

MoveInfo SinePattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo;
	if (lpObject)
	{
		//사인처럼 움직이게 각도값을 계속 변경...할수가있나? 값 계산 방법 고민
		//sin 미분 -> cos , cos 미분 -> -sin 인걸로 1차함수 그래프 만들어봄
		
		//lpObject->angle += (PI / 4  - lpObject->elapsedTime * deltaTime);
		float angle = PI / 5;
		float ratio = lpObject->elapsedTime - (int)lpObject->elapsedTime;
		if (((int)lpObject->elapsedTime) % 2 != 0)
		{
			ratio = -ratio - 0.0000001f;
		}

		moveInfo.angle = PI / 2;
		moveInfo.deltaPos = { (int)lpObject->elapsedTime * cosf(lpObject->angle) * lpObject->speed, (int)lpObject->elapsedTime * sinf(lpObject->angle) * lpObject->speed };

		POINTFLOAT p1, p2, p3;
		float angleB = lpObject->angle - angle;
		float angleC = lpObject->angle + angle;
		float baseDist = lpObject->speed * 0.5f / cosf(angle);
		if (ratio > 0)
		{
			p1.x = cosf(angleB) * baseDist * ratio;
			p1.y = sinf(angleB) * baseDist * ratio;

			p2.x = cosf(angleB) * baseDist + cosf(angleC) * baseDist * ratio;
			p2.y = sinf(angleB) * baseDist + sinf(angleC) * baseDist * ratio;
		}
		else
		{
			p1.x = cosf(angleC) * baseDist * abs(ratio);
			p1.y = sinf(angleC) * baseDist * abs(ratio);

			p2.x = cosf(angleC) * baseDist + cosf(angleB) * baseDist * abs(ratio);
			p2.y = sinf(angleC) * baseDist + sinf(angleB) * baseDist * abs(ratio);
		}

		p3.x = p1.x + (p2.x - p1.x) * abs(ratio);
		p3.y = p1.y + (p2.y - p1.y) * abs(ratio);

		moveInfo.deltaPos.x += p3.x;
		moveInfo.deltaPos.y += p3.y;

		//lpObject->pos.x += lpObject->speed * deltaTime * cos(lpObject->angle);
		//lpObject->pos.y += lpObject->speed * deltaTime * sin(lpObject->angle);

	}
	return moveInfo;
}
