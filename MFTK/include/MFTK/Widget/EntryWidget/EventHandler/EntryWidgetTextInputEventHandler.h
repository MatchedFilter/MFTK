#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetTextInputEventHandler.h"

namespace MFTK
{
    class EntryWidgetTextInputEventHandler : public IWidgetTextInputEventHandler
    {
    public:
        EntryWidgetTextInputEventHandler() = default;
        virtual ~EntryWidgetTextInputEventHandler() = default;
        virtual void OnTextInput(Widget *widget, const SDL_Event *event) override;
    };
}
