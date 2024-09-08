#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetOnFocusOnEventHandler.h"

namespace MFTK
{
    class EntryWidgetOnFocusOnEventHandler : public IWidgetOnFocusOnEventHandler
    {
    public:
        EntryWidgetOnFocusOnEventHandler() = default;
        virtual ~EntryWidgetOnFocusOnEventHandler() = default;
        virtual void OnFocusOn(Widget *widget, const SDL_Event *event) override;
    };
}
