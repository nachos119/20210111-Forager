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
	delete timer;
}

void TimerManager::Update()
{
	if (timer)
		timer->Tick();
}

void TimerManager::Render(HDC hdc)
{
	if (timer)
	{
		wsprintf(szText, "FPS : %d", timer->GetFPS());
		TextOut(hdc, WINSIZE_MAP_X - 100, 20, szText, strlen(szText));
	}
}

void TimerManager::SetIsSC_MOVE(bool isSC_MOVE)
{
	timer->SetIsSC_MOVE(isSC_MOVE);
}

float TimerManager::GetTimeScale()
{
	return timer->GetTimeScale();
}

float TimerManager::GetElapsedTime()
{
	return timer->GetElapsedTime();
}
