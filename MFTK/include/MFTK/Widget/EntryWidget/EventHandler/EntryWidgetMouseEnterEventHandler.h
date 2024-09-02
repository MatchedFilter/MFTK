#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetMouseEnterEventHandler.h"

namespace MFTK
{
    class EntryWidgetMouseEnterEventHandler : public IWidgetMouseEnterEventHandler
    {
    public:
        EntryWidgetMouseEnterEventHandler() = default;
        virtual ~EntryWidgetMouseEnterEventHandler() = default;
        virtual void OnEnter(Widget *widget, const SDL_Event *event) override;
    };
}
