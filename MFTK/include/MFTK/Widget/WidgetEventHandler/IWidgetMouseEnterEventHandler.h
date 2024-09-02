#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetMouseEnterEventHandler
    {
    public:
        virtual ~IWidgetMouseEnterEventHandler() = default;
        virtual void OnEnter(Widget *widget, const SDL_Event *event) = 0;
    };
}
