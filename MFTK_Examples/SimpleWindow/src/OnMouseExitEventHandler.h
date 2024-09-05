#pragma once
#include "MFTK/Tk.h"
#include "MFTK/Widget/WidgetEventHandler/IWidgetMouseExitEventHandler.h"
#include <iostream>

class OnMouseExitEventHandler : public MFTK::IWidgetMouseExitEventHandler
{
public:
    OnMouseExitEventHandler() = default;
    ~OnMouseExitEventHandler() = default;
    virtual void OnExit(MFTK::Widget *widget, const SDL_Event *event) override
    {
        std::cout << "[Exit] x: " << event->motion.x << ", y: " << event->motion.y << "\n";
        MFTK::Tk::ChangeCursor(SDL_SYSTEM_CURSOR_ARROW);
    }
};