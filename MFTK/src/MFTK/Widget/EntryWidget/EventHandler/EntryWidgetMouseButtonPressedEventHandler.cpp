#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseButtonPressedEventHandler.h"
#include "MFTK/Widget/EntryWidget/EntryWidget.h"

using namespace MFTK;

void EntryWidgetMouseButtonPressedEventHandler::OnMouseButtonPressed(Widget *widget, const SDL_Event *event)
{
    EntryWidget *eWidget = static_cast<EntryWidget*>(widget);
    Sint32 caretIndex = eWidget->GetCaretIndex();
    size_t textLength = SDL_utf8strlen(eWidget->GetText());
    if (textLength > 0)
    {
        SDL_Rect position = widget->GetWidgetPosition();
        int mouseClickedRelativeXPos = event->motion.x -  position.x;
        int caretDisplayIndexOffset = static_cast<Sint32>(static_cast<double>(mouseClickedRelativeXPos) / static_cast<double>(eWidget->GetPixelPerChar()));
        caretIndex = eWidget->GetDisplayStartIndex() + caretDisplayIndexOffset;
        if (caretIndex > textLength)
        {
            caretIndex = textLength;
        }
    }

    eWidget->SetCaretIndex(caretIndex);
}

