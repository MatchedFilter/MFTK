#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetKeyPressedEventHandler
    {
    public:
        virtual ~IWidgetKeyPressedEventHandler() = default;
        virtual void OnKeyPressed(Widget *widget, const SDL_Event *event) = 0;
    };
}
