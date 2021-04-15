#include "timer.h"

HRESULT Timer::Init()
{
	hasGoodHardWare = false;
	timeScale = 0.0f;		// 경과 진동수/초당 진동수 -> 한 루프가 도는 동안의 시간
	elapsedTime = 0.0f;		// 경과 시간 : 현재시간 - 이전에 체크한 시간(last time)
	currTime = 0.0;			// 현재 시간
	lastTime = 0.0;			// 마지막에 체크한 시간
	periodFrequency = 0.0;	// 

	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;
	
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))	//고해상도 타이머의 주기(1초당 진동수) 반환
	{
		hasGoodHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);	
		//수행시간동안 발생한 진동수 반환, 함수가 호출된 시점(여기선 라스트 타임)에 고해상도 타이머 값 설정
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		hasGoodHardWare = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}
    return S_OK;
}

void Timer::Tick()
{
	if (hasGoodHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}
	elapsedTime = (currTime - lastTime) * timeScale;

	fpsTimeElapsed += elapsedTime;
	fpsFrameCount++;

	if (fpsTimeElapsed >= 1.0f)
	{
		FPS = fpsFrameCount;
		fpsFrameCount = 0.0f;
		fpsTimeElapsed -= 1.0f;
	}
	lastTime = currTime;
}

float Timer::GetCurrTime()
{
	__int64 time;
	if (hasGoodHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&time);
	}
	else
	{
		time = timeGetTime();
	}
    return time/timeScale;
}
