#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
    lpTimer = new Timer();
    lpTimer->Init();

    return S_OK;
}

void TimerManager::Release()
{
    if (lpTimer)
    {
        delete lpTimer;
        lpTimer = nullptr;
    }

}

void TimerManager::Update()
{
    if (lpTimer)
    {
        lpTimer->Tick();
    }
}

void TimerManager::Render(HDC hdc)
{
    if (lpTimer)
    {
        //확인용 출력
        wsprintf(szText, "FPS : %d", lpTimer->GetFPS());
        TextOut(hdc, WINSIZE_WIDTH - 150, 20, szText, strlen(szText));
    }
}

float TimerManager::GetDeltaTime()
{
    return lpTimer->GetDeltaTime();
}