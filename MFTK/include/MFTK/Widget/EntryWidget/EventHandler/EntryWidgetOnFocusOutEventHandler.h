#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetOnFocusOutEventHandler.h"

namespace MFTK
{
    class EntryWidgetOnFocusOutEventHandler : public IWidgetOnFocusOutEventHandler
    {
    public:
        EntryWidgetOnFocusOutEventHandler() = default;
        virtual ~EntryWidgetOnFocusOutEventHandler() = default;
        virtual void OnFocusOut(Widget *widget, const SDL_Event *event) override;
    };
}
