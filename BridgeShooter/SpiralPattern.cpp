#include "SpiralPattern.h"
#include "GameObject.h"

void SpiralPattern::Move(float deltaTime, GameObject* lpObject)
{
    /*
        lpObject->origin : 탄의 첫 발사 각도
        lpObject->speed : 탄의 속도로 픽셀값이 아닌 PI 값을 기준으로 한다
        lpObject->period : 실제 계산할 탄의 속도 매번 speed로 계산해주기에 초기값이 의미 없다
        lpObject->pos : 실제 위치
        lpObject->amplitude : 탄의 기울기 작을수록 많이 휜다.

        speed : PI 값으로 조절하고 이 PI에 -1 곱하면 역방향 패턴이 된다.
        amplitue / speed : 스피드를 조정할 경우 곡률이 변한다.
        스피드의 증가량만큼 amplitude 를 줄여주어야 곡률을 유지하면서 속도를 줄일 수 있다.

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
