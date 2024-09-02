#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetMouseButtonReleasedEventHandler
    {
    public:
        virtual ~IWidgetMouseButtonReleasedEventHandler() = default;
        virtual void OnMouseButtonReleased(Widget *widget, const SDL_Event *event) = 0;
    };
}
