#include "timer.h"

HRESULT Timer::Init()
{
	hasGoodHardWare = false;
	timeScale = 0.0f;		// ��� ������/�ʴ� ������ -> �� ������ ���� ������ �ð�
	elapsedTime = 0.0f;		// ��� �ð� : ����ð� - ������ üũ�� �ð�(last time)
	currTime = 0.0;			// ���� �ð�
	lastTime = 0.0;			// �������� üũ�� �ð�
	periodFrequency = 0.0;	// 

	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;
	
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))	//���ػ� Ÿ�̸��� �ֱ�(1�ʴ� ������) ��ȯ
	{
		hasGoodHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);	
		//����ð����� �߻��� ������ ��ȯ, �Լ��� ȣ��� ����(���⼱ ��Ʈ Ÿ��)�� ���ػ� Ÿ�̸� �� ����
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
