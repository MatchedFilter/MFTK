#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetClickedEventHandler
    {
    public:
        virtual ~IWidgetClickedEventHandler() = default;
        virtual void OnWidgetClicked(Widget *widget, const SDL_Event *event) = 0;
    };
}
