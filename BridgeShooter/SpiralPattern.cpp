#include "SpiralPattern.h"
#include "GameObject.h"

MoveInfo SpiralPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = {};

    /*
        lpObject->origin : ź�� ù �߻� ����
        lpObject->speed : ź�� �ӵ��� �ȼ����� �ƴ� PI ���� �������� �Ѵ�
        lpObject->period : ���� ����� ź�� �ӵ� �Ź� speed�� ������ֱ⿡ �ʱⰪ�� �ǹ� ����
        lpObject->pos : ���� ��ġ
        lpObject->amplitude : ź�� ���� �������� ���� �ش�.
    */

    float dir = lpObject->speed / abs(lpObject->speed);
    lpObject->period = lpObject->speed * pow(9.0f / 10.0f, 1 + log(lpObject->elapsedTime + 1));
    lpObject->pos.x = lpObject->origin.x + cosf(lpObject->angle) * lpObject->amplitude * sqrt(lpObject->elapsedTime);
    lpObject->pos.y = lpObject->origin.y + sinf(lpObject->angle) * lpObject->amplitude * sqrt(lpObject->elapsedTime);
    lpObject->angle = lpObject->originAngle + lpObject->period * sqrt(lpObject->elapsedTime);

    return moveInfo;
}
