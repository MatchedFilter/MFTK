#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetKeyReleasedEventHandler
    {
    public:
        virtual ~IWidgetKeyReleasedEventHandler() = default;
        virtual void OnKeyReleased(Widget *widget, const SDL_Event *event) = 0;
    };
}
