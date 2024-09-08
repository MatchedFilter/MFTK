#pragma once
#include <SDL_stdinc.h>
#include "ITimerOnTimeoutHandler.h"

namespace MFTK
{
    class Timer
    {
    public:
        Timer(Sint32 durationInMillisecond, bool isPeriodic, ITimerOnTimeoutHandler *timeoutHandler);
        ~Timer() = default;
        void Update(Sint32 durationInMillisecond);
        void Start();
        void Stop();
        void Run();

        bool IsRunning() const { return m_bIsRunning; }

    private:
        Sint32 m_DurationInMillisecond;
        const bool m_bIsPeriodic;
        ITimerOnTimeoutHandler *m_TimeoutHandler;
        Uint64 m_StartTimestampInMillisecond;
        bool m_bIsRunning;
    };
} // namespace MFTK
