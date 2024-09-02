#pragma once
#include "MFTK/Widget/WidgetEventHandler/IWidgetMouseExitEventHandler.h"

namespace MFTK
{
    class EntryWidgetMouseExitEventHandler : public IWidgetMouseExitEventHandler
    {
    public:
        EntryWidgetMouseExitEventHandler() = default;
        virtual ~EntryWidgetMouseExitEventHandler() = default;
        virtual void OnExit(Widget *widget, const SDL_Event *event) override;
    };
}
