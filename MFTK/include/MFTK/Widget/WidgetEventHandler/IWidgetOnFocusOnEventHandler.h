#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetOnFocusOnEventHandler
    {
    public:
        virtual ~IWidgetOnFocusOnEventHandler() = default;
        virtual void OnFocusOn(Widget *widget, const SDL_Event *event) = 0;
    };
}
