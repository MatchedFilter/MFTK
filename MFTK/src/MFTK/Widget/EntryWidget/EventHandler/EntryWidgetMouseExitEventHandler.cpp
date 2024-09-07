#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseExitEventHandler.h"
#include "MFTK/ResourceManager/ResourceManager.h"

using namespace MFTK;

void EntryWidgetMouseExitEventHandler::OnExit(Widget *widget, const SDL_Event *event)
{
    ResourceManager::ChangeCursor(SDL_SYSTEM_CURSOR_ARROW);
}

