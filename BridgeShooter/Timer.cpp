#include "timer.h"

HRESULT Timer::Init()
{
	hasGoodHardWare = false;
	timeScale = 0.0f;		// 경과 진동수/초당 진동수 -> 한 루프가 도는 동안의 시간
	elapsedTime = 0.0f;
	currTime = 0.0;
	lastTime = 0.0;
	periodFrequency = 0.0;

	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;
	
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		hasGoodHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
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
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
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
