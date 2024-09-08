#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetTextInputEventHandler.h"
#include "MFTK/Widget/EntryWidget/EntryWidget.h"
#include "SDL.h"
#include <iostream>

using namespace MFTK;

void EntryWidgetTextInputEventHandler::OnTextInput(Widget *widget, const SDL_Event *event)
{
    EntryWidget *eWidget = static_cast<EntryWidget*>(widget);
    eWidget->OnTextInsert(event->text.text);
}
