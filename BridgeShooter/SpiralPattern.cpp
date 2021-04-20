#include "SpiralPattern.h"
#include "GameObject.h"

MoveInfo SpiralPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = {};

    /*
        lpObject->origin : 탄의 첫 발사 각도
        lpObject->speed : 탄의 속도로 픽셀값이 아닌 PI 값을 기준으로 한다
        lpObject->period : 실제 계산할 탄의 속도 매번 speed로 계산해주기에 초기값이 의미 없다
        lpObject->pos : 실제 위치
        lpObject->amplitude : 탄의 기울기 작을수록 많이 휜다.
    */

    float dir = lpObject->speed / abs(lpObject->speed);
    lpObject->period = lpObject->speed * pow(9.0f / 10.0f, 1 + log(lpObject->elapsedTime + 1));
    lpObject->pos.x = lpObject->origin.x + cosf(lpObject->angle) * lpObject->amplitude * sqrt(lpObject->elapsedTime);
    lpObject->pos.y = lpObject->origin.y + sinf(lpObject->angle) * lpObject->amplitude * sqrt(lpObject->elapsedTime);
    lpObject->angle = lpObject->originAngle + lpObject->period * sqrt(lpObject->elapsedTime);

    return moveInfo;
}
