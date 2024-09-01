#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetHoverEventHandler
    {
    public:
        virtual ~IWidgetHoverEventHandler() = default;
        virtual void OnHover(Widget *widget, const SDL_Event *event) = 0;
    };
}
