#include "MFTK/Common/Time/Timer.h"
#include <SDL.h>

using namespace MFTK;


Timer::Timer(int32_t durationInMillisecond, bool isPeriodic, ITimerOnTimeoutHandler *timeoutHandler) : 
    m_DurationInMillisecond{ durationInMillisecond },
    m_bIsPeriodic { isPeriodic },
    m_TimeoutHandler { timeoutHandler},
    m_StartTimestampInMillisecond { 0 },
    m_bIsRunning { false }
{
}

void Timer::Update(Sint32 durationInMillisecond)
{
    m_DurationInMillisecond = durationInMillisecond;    
}

void Timer::Start()
{
    m_StartTimestampInMillisecond = SDL_GetTicks64();
    m_bIsRunning = true;
}

void Timer::Stop()
{
    m_bIsRunning = false;
}

void Timer::Run()
{
    if (IsRunning())
    {
        Uint64 currentTimestampInMillisecond = SDL_GetTicks64();
        if (currentTimestampInMillisecond >= m_StartTimestampInMillisecond + static_cast<Uint64>(m_DurationInMillisecond))
        {
            m_bIsRunning = false;
            m_TimeoutHandler->OnTimeout();
        }
        if (!IsRunning() && m_bIsPeriodic)
        {
            m_bIsRunning = true;
            m_StartTimestampInMillisecond = SDL_GetTicks64();
        }
    }
}