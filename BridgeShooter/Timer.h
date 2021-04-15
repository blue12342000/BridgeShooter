#pragma once
#include "BridgeShooter.h"

class Timer
{
private:
	bool hasGoodHardWare;
	float timeScale;		//��� ������/�ʴ� ������ -> �׷��� ���������� ����� ������ �ð��� ��������?
	float elapsedTime;
	__int64 currTime;
	__int64 lastTime;
	__int64 periodFrequency;

	float fpsTimeElapsed;
	unsigned long fpsFrameCount;
	unsigned long FPS;

public:
	HRESULT Init();
	void Tick();
	float GetCurrTime();

	inline unsigned long GetFPS() { return this->FPS; }
	inline float GetElapsedTime() { return this->elapsedTime; }

};

