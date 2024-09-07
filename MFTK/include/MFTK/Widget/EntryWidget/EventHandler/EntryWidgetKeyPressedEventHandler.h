#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetKeyPressedEventHandler.h"

namespace MFTK
{
    class EntryWidgetKeyPressedEventHandler : public IWidgetKeyPressedEventHandler
    {
    public:
        EntryWidgetKeyPressedEventHandler() = default;
        virtual ~EntryWidgetKeyPressedEventHandler() = default;
        virtual void OnKeyPressed(Widget *widget, const SDL_Event *event) override;
    };
}
