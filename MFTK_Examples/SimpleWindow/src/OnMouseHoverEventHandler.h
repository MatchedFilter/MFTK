#pragma once
#include "MFTK/Tk.h"
#include "MFTK/Widget/WidgetEventHandler/IWidgetHoverEventHandler.h"
#include <iostream>

class OnMouseHoverEventHandler : public MFTK::IWidgetHoverEventHandler
{
public:
    OnMouseHoverEventHandler() = default;
    ~OnMouseHoverEventHandler() = default;
    virtual void OnHover(MFTK::Widget *widget, const SDL_Event *event) override
    {
        std::cout << "[Hover] x: " << event->motion.x << ", y: " << event->motion.y << "\n";
        MFTK::Tk::ChangeCursor(SDL_SYSTEM_CURSOR_HAND);
    }
};