#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetOnFocusOutEventHandler
    {
    public:
        virtual ~IWidgetOnFocusOutEventHandler() = default;
        virtual void OnFocusOut(Widget *widget, const SDL_Event *event) = 0;
    };
}
