#include "timer.h"

HRESULT Timer::Init()
{
	hasGoodHardWare = false;
	timeScale = 0.0f;		// 경과 진동수/초당 진동수 -> 한 루프가 도는 동안의 시간
	elapsedTime = 0.0f;		// 경과 시간 : 현재시간 - 이전에 체크한 시간(last time)
	currTime = 0.0;			// 현재 시간
	lastTime = 0.0;			// 마지막에 체크한 시간
	periodFrequency = 0.0;	// 1초당 진동수 저장할 변수

	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;
	
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))	//고해상도 1초당 진동수(돈 루프 수) 반환
	{
		hasGoodHardWare = true;

		//수행시간동안 발생한 진동수 반환, 함수가 호출된 시점(여기선 라스트 타임)에 고해상도 타이머 값 설정
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);	
		
		//periodFrequency - 1초에 몇루프 도는가(진동수)이므로 timeScale -한 루프 도는데 걸리는 시간은
		// 1s : periodFrequency루프 = timeScale : 1루프 -> 비례식 계산
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		hasGoodHardWare = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;		//대략적인 계산 - 원래하던 SetTimer와 같다.
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
		// timeGetTime() 윈도우 시작되고 지금까지 흐른 시간을 반환하는 함수
		currTime = timeGetTime();
	}

	//밑에 함수에서나, QueryPerformanceConter 함수 기능도 그렇고, currtime은 수행시간동안 발생한 총 진동수다.
	//currTime은(lastTime도 본질적으론 같으니 마찬가지로) time(지금까지 걸린 시간) / timeScale 이므로
	//지금까지 돈 총 루프 수가 나온다. 그걸 다시 시간으로 바꿔주려면 timeScale 곱해야 함.

	//elapsedTime : currTime(지금까지의 총 루프수(진동수)) = timeScale(1루프에 걸리는 시간) : 1(루프)
	//비례식으로 표현하면 다음과 같다.
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
