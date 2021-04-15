#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
    timer = new Timer();
    timer->Init();

    return S_OK;
}

void TimerManager::Release()
{
    if (timer)
    {
        delete timer;
        timer = nullptr;
    }

}

void TimerManager::Update()
{
    if (timer)
    {
        timer->Tick();
    }
}

void TimerManager::Render(HDC hdc)
{
    if (timer)
    {
        //Ȯ�ο� ���
        wsprintf(szText, "FPS : %d", timer->GetFPS());
        TextOut(hdc, WINSIZE_WIDTH - 150, 20, szText, strlen(szText));
    }
}

float TimerManager::GetDeltaTime()
{
    return timer->GetDeltaTime();
}