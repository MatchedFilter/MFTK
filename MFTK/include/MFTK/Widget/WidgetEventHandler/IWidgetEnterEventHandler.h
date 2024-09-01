#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetEnterEventHandler
    {
    public:
        virtual ~IWidgetEnterEventHandler() = default;
        virtual void OnEnter(Widget *widget, const SDL_Event *event) = 0;
    };
}
