#include "SpiralPattern.h"
#include "GameObject.h"

void SpiralPattern::Move(float deltaTime, GameObject* lpObject)
{
    /*
        lpObject->origin : ź�� ù �߻� ����
        lpObject->speed : ź�� �ӵ��� �ȼ����� �ƴ� PI ���� �������� �Ѵ�
        lpObject->period : ���� ����� ź�� �ӵ� �Ź� speed�� ������ֱ⿡ �ʱⰪ�� �ǹ� ����
        lpObject->pos : ���� ��ġ
        lpObject->amplitude : ź�� ���� �������� ���� �ش�.

        speed : PI ������ �����ϰ� �� PI�� -1 ���ϸ� ������ ������ �ȴ�.
        amplitue / speed : ���ǵ带 ������ ��� ����� ���Ѵ�.
        ���ǵ��� ��������ŭ amplitude �� �ٿ��־�� ����� �����ϸ鼭 �ӵ��� ���� �� �ִ�.

    */

    Transform& transform = lpObject->transform;
    float dir = transform.speed / abs(transform.speed);
    transform.period = transform.speed * pow(9.0f / 10.0f, 1 + log(lpObject->elapsedTime + 1));
    lpObject->pos.x = transform.pos.x + cosf(lpObject->angle) * transform.amplitude * sqrt(lpObject->elapsedTime);
    lpObject->pos.y = transform.pos.y + sinf(lpObject->angle) * transform.amplitude * sqrt(lpObject->elapsedTime);
    lpObject->angle = transform.angle + transform.period * sqrt(lpObject->elapsedTime);

    //float dir = lpObject->speed / abs(lpObject->speed);
    //lpObject->period = lpObject->speed * pow(9.0f / 10.0f, 1 + log(lpObject->elapsedTime + 1));
    //lpObject->pos.x = lpObject->origin.x + cosf(lpObject->angle) * lpObject->amplitude * sqrt(lpObject->elapsedTime);
    //lpObject->pos.y = lpObject->origin.y + sinf(lpObject->angle) * lpObject->amplitude * sqrt(lpObject->elapsedTime);
    //lpObject->angle = lpObject->originAngle + lpObject->period * sqrt(lpObject->elapsedTime);
}
