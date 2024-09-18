#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetKeyPressedEventHandler.h"
#include "MFTK/Widget/EntryWidget/EntryWidget.h"
using namespace MFTK;

void EntryWidgetKeyPressedEventHandler::OnKeyPressed(Widget *widget, const SDL_Event *event)
{
    EntryWidget *eWidget = static_cast<EntryWidget*>(widget);
    if (widget->IsFocused())
    {

        switch (event->key.keysym.sym)
        {
        case SDLK_BACKSPACE:
        {
            eWidget->OnBackspace();
        }
        break;

        case SDLK_RIGHT:
        {
            if (eWidget->GetCaretIndex() < eWidget->GetUtf32TextSize())
            {
                eWidget->m_CaretBlinkTimer.Start();
                eWidget->m_CaretBlinkTimerTimeoutHandler.TurnOn();
                eWidget->SetCaretIndex(eWidget->GetCaretIndex() + 1);
            }
        }
        break;

        case SDLK_LEFT:
        {
            if (eWidget->GetCaretIndex() > 0)
            {
                eWidget->m_CaretBlinkTimer.Start();
                eWidget->m_CaretBlinkTimerTimeoutHandler.TurnOn();
                eWidget->SetCaretIndex(eWidget->GetCaretIndex() - 1);
            }
        }
        break;
        
        default:
            break;
        }
    }
}

