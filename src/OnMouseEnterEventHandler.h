#pragma once
#include "MFTK/Tk.h"
#include "MFTK/Widget/WidgetEventHandler/IWidgetMouseEnterEventHandler.h"
#include <iostream>

class OnMouseEnterEventHandler : public MFTK::IWidgetMouseEnterEventHandler
{
public:
    OnMouseEnterEventHandler() = default;
    ~OnMouseEnterEventHandler() = default;
    virtual void OnEnter(MFTK::Widget *widget, const SDL_Event *event) override
    {
        std::cout << "[Enter] x: " << event->motion.x << ", y: " << event->motion.y << "\n";
        MFTK::Tk::ChangeCursor(SDL_SYSTEM_CURSOR_HAND);
    }
};