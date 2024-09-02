#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetMouseButtonPressedEventHandler
    {
    public:
        virtual ~IWidgetMouseButtonPressedEventHandler() = default;
        virtual void OnMouseButtonPressed(Widget *widget, const SDL_Event *event) = 0;
    };
}
