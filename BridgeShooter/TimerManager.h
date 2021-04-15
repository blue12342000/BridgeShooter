#pragma once
#include "Singleton.h"
#include "BridgeShooter.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* timer;
	char szText[128];	//타이머 확인용

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetElapsedTime();
	float GetCurrTime();
};

