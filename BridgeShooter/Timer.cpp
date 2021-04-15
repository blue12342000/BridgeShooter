#include "timer.h"

HRESULT Timer::Init()
{
	hasGoodHardWare = false;
	timeScale = 0.0f;		// ��� ������/�ʴ� ������ -> �� ������ ���� ������ �ð�
	elapsedTime = 0.0f;		// ��� �ð� : ����ð� - ������ üũ�� �ð�(last time)
	currTime = 0.0;			// ���� �ð�
	lastTime = 0.0;			// �������� üũ�� �ð�
	periodFrequency = 0.0;	// 1�ʴ� ������ ������ ����

	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;
	
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))	//���ػ� 1�ʴ� ������(�� ���� ��) ��ȯ
	{
		hasGoodHardWare = true;

		//����ð����� �߻��� ������ ��ȯ, �Լ��� ȣ��� ����(���⼱ ��Ʈ Ÿ��)�� ���ػ� Ÿ�̸� �� ����
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);	
		
		//periodFrequency - 1�ʿ� ����� ���°�(������)�̹Ƿ� timeScale -�� ���� ���µ� �ɸ��� �ð���
		// 1s : periodFrequency���� = timeScale : 1���� -> ��ʽ� ���
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		hasGoodHardWare = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;		//�뷫���� ��� - �����ϴ� SetTimer�� ����.
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
		// timeGetTime() ������ ���۵ǰ� ���ݱ��� �帥 �ð��� ��ȯ�ϴ� �Լ�
		currTime = timeGetTime();
	}

	//�ؿ� �Լ�������, QueryPerformanceConter �Լ� ��ɵ� �׷���, currtime�� ����ð����� �߻��� �� ��������.
	//currTime��(lastTime�� ���������� ������ ����������) time(���ݱ��� �ɸ� �ð�) / timeScale �̹Ƿ�
	//���ݱ��� �� �� ���� ���� ���´�. �װ� �ٽ� �ð����� �ٲ��ַ��� timeScale ���ؾ� ��.

	//elapsedTime : currTime(���ݱ����� �� ������(������)) = timeScale(1������ �ɸ��� �ð�) : 1(����)
	//��ʽ����� ǥ���ϸ� ������ ����.
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
