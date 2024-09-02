#include "MFTK/Widget/EntryWidget/EntryWidget.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseEnterEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseExitEventHandler.h"

using namespace MFTK;

EntryWidget::EntryWidget(Window *window, Sint32 w, Sint32 h) :
    Widget { window, w, h},
    m_bIsMouseEnterEventUpdated { false },
    m_bIsMouseExitEventUpdated { false }
{
    m_WidgetMouseEnterEventHandler = new EntryWidgetMouseEnterEventHandler();
    m_WidgetMouseExitEventHandler = new EntryWidgetMouseExitEventHandler();
}

EntryWidget::~EntryWidget()
{
}

void EntryWidget::SetWidgetMouseEnterEventHandler(IWidgetMouseEnterEventHandler *widgetMouseEnterEventHandler)
{
    Widget::SetWidgetMouseEnterEventHandler(widgetMouseEnterEventHandler);
    m_bIsMouseEnterEventUpdated = true;
}

void EntryWidget::SetWidgetMouseExitEventHandler(IWidgetMouseExitEventHandler *widgetMouseExitEventHandler)
{
    Widget::SetWidgetMouseExitEventHandler(widgetMouseExitEventHandler);
    m_bIsMouseExitEventUpdated = true;
}

void EntryWidget::Destroy()
{
    if (m_WidgetMouseEnterEventHandler != nullptr)
    {
        if (!m_bIsMouseEnterEventUpdated)
        {
            delete m_WidgetMouseEnterEventHandler;
            m_WidgetMouseEnterEventHandler = nullptr;
        }
    }
    if (m_WidgetMouseExitEventHandler != nullptr)
    {
        if (!m_bIsMouseExitEventUpdated)
        {
            delete m_WidgetMouseEnterEventHandler;
            m_WidgetMouseEnterEventHandler = nullptr;
        }
    }
}
