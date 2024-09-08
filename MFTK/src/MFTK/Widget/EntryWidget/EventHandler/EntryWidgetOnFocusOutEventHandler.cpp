#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetOnFocusOutEventHandler.h"
#include "MFTK/Widget/EntryWidget/EntryWidget.h"
#include "SDL.h"
using namespace MFTK;

void EntryWidgetOnFocusOutEventHandler::OnFocusOut(Widget *widget, const SDL_Event *event)
{
    SDL_StopTextInput();
    EntryWidget* eWidget = static_cast<EntryWidget*>(widget);
    eWidget->m_CaretBlinkTimer.Stop();
    eWidget->m_CaretBlinkTimerTimeoutHandler.TurnOff();
}
