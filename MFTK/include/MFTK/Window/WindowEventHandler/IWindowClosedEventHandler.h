#pragma once

namespace MFTK
{
    class IWindowClosedEventHandler
    {
    public:
        virtual ~IWindowClosedEventHandler() = default;
        virtual void OnWindowClosed() = 0;
    };
} // namespace MFTK
