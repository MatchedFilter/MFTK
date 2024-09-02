#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetMouseExitEventHandler
    {
    public:
        virtual ~IWidgetMouseExitEventHandler() = default;
        virtual void OnExit(Widget *widget, const SDL_Event *event) = 0;
    };
}
