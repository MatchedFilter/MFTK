#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetMouseButtonPressedEventHandler.h"

namespace MFTK
{
    class EntryWidgetMouseButtonPressedEventHandler : public IWidgetMouseButtonPressedEventHandler
    {
    public:
        EntryWidgetMouseButtonPressedEventHandler() = default;
        virtual ~EntryWidgetMouseButtonPressedEventHandler() = default;
        virtual void OnMouseButtonPressed(Widget *widget, const SDL_Event *event) override;
    };
}
