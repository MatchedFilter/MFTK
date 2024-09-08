#pragma once

namespace MFTK
{
    class ITimerOnTimeoutHandler
    {
    public:
        virtual ~ITimerOnTimeoutHandler() = default;
        virtual void OnTimeout() = 0;
    };
} // namespace MFTK
