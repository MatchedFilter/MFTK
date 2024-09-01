#pragma once
#include "MFTK/Tk.h"
#include "MFTK/Window/WindowEventHandler/IWindowClosedEventHandler.h"

class OnMainWindowClosedEventHandler : public MFTK::IWindowClosedEventHandler
{
public:
    OnMainWindowClosedEventHandler() = default;
    ~OnMainWindowClosedEventHandler() = default;
    virtual void OnWindowClosed() { MFTK::Tk::DestroyApplication(); }
};