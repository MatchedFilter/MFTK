#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseExitEventHandler.h"
#include "MFTK/Tk.h"

using namespace MFTK;

void EntryWidgetMouseExitEventHandler::OnExit(Widget *widget, const SDL_Event *event)
{
    Tk::ChangeCursor(SDL_SYSTEM_CURSOR_ARROW);
}

