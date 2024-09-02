#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseEnterEventHandler.h"
#include "MFTK/Tk.h"

using namespace MFTK;

void EntryWidgetMouseEnterEventHandler::OnEnter(Widget *widget, const SDL_Event *event)
{
    Tk::ChangeCursor(SDL_SYSTEM_CURSOR_IBEAM);
}

