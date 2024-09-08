#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseEnterEventHandler.h"
#include "MFTK/ResourceManager/ResourceManager.h"

using namespace MFTK;

void EntryWidgetMouseEnterEventHandler::OnEnter(Widget *widget, const SDL_Event *event)
{
    ResourceManager::ChangeCursor(SDL_SYSTEM_CURSOR_IBEAM);
}
