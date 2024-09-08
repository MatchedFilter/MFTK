#pragma once
#include <SDL_events.h>

namespace MFTK
{
    class Widget;
    class IWidgetTextInputEventHandler
    {
    public:
        virtual ~IWidgetTextInputEventHandler() = default;
        virtual void OnTextInput(Widget *widget, const SDL_Event *event) = 0;
    };
}
