#pragma once
#include "MFTK/Common/Time/ITimerOnTimeoutHandler.h"

namespace MFTK
{
    class CaretBlinkTimerTimeoutHandler : public ITimerOnTimeoutHandler
    {
    public:
        CaretBlinkTimerTimeoutHandler() : m_bIsTurnedOn { false } { }
        bool IsTurnedOn() const { return m_bIsTurnedOn; }
        virtual void OnTimeout() {
            if (m_bIsTurnedOn)
            {
                m_bIsTurnedOn = false;
            }
            else
            {
                m_bIsTurnedOn = true;
            }
        }
        void TurnOff() { m_bIsTurnedOn = false; }
        void TurnOn() { m_bIsTurnedOn = true; }

    private:
        bool m_bIsTurnedOn;
    };
    
} // namespace MFTK
