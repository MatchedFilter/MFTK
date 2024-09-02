#pragma once
#include "MFTK/Widget/Widget.h"


namespace MFTK
{
    class EntryWidget: public Widget
    {
    public:
        EntryWidget(Window *window, Sint32 w, Sint32 h);
        virtual ~EntryWidget();
        virtual void Destroy() override;

        virtual void SetWidgetMouseEnterEventHandler(IWidgetMouseEnterEventHandler *widgetMouseEnterEventHandler) override;
        virtual void SetWidgetMouseExitEventHandler(IWidgetMouseExitEventHandler *widgetMouseExitEventHandler) override;

    private:
        bool m_bIsMouseEnterEventUpdated;
        bool m_bIsMouseExitEventUpdated;

    };
    
} // namespace MFTK
