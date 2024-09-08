#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetOnFocusOnEventHandler.h"
#include "MFTK/Widget/EntryWidget/EntryWidget.h"
#include "SDL.h"

using namespace MFTK;

void EntryWidgetOnFocusOnEventHandler::OnFocusOn(Widget *widget, const SDL_Event *event)
{
    EntryWidget* eWidget = static_cast<EntryWidget*>(widget);
    if (eWidget->IsFocused())
    {
        SDL_Rect positionRect = eWidget->GetWidgetPosition();
        SDL_SetTextInputRect(&positionRect);
        eWidget->m_CaretBlinkTimer.Start();
        eWidget->m_CaretBlinkTimerTimeoutHandler.TurnOn();
        SDL_StartTextInput();
    }
}
