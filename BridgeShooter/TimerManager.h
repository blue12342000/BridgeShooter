#pragma once
#include "BridgeShooter.h"
#include "Singleton.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* lpTimer;
	char szText[128];

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetDeltaTime();
};

