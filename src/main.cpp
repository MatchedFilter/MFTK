#include "MFTK/Tk.h"
#include "OnMainWindowClosedEventHandler.h"
#include "OnMouseClickedEventHandler.h"
#include "OnMouseHoverEventHandler.h"
#include "OnMouseEnterEventHandler.h"
#include "OnMouseExitEventHandler.h"
#include "MFTK/Widget/Widget.h"


int main(int argc, char *argv[])
{
    OnMainWindowClosedEventHandler onMainWindowClosedEventHandler;
    OnMouseClickedEventHandler onMouseClickedEventHandler;
    OnMouseHoverEventHandler onMouseHoverEventHandler;
    OnMouseEnterEventHandler onMouseEnterEventHandler;
    OnMouseExitEventHandler onMouseExitEventHandler;

    MFTK::Tk::Initialize(120);
    
    MFTK::Window *mainWindow = new MFTK::Window(800, 600, "Main Window");
    mainWindow->SetBgColor({.r = 30, .g = 30, .b = 30, .a = 255});
    mainWindow->SetWindowClosedEventHandler(&onMainWindowClosedEventHandler);

    MFTK::Window *window2 = new MFTK::Window(800, 600, "Window 2");
    window2->SetBgColor({.r = 53, .g = 102, .b = 98, .a = 255});


    MFTK::Widget widget1(mainWindow, 50, 20);
    widget1.SetWidgetClickedEventHandler(&onMouseClickedEventHandler);
    widget1.SetWidgetHoverEventHandler(&onMouseHoverEventHandler);
    widget1.SetWidgetExitEventHandler(&onMouseExitEventHandler);

    MFTK::Widget widget2(window2, 200, 30);
    widget2.SetWidgetClickedEventHandler(&onMouseClickedEventHandler);
    widget2.SetWidgetEnterEventHandler(&onMouseEnterEventHandler);
    widget2.SetWidgetExitEventHandler(&onMouseExitEventHandler);

    widget1.Grid({.row = 0, .column = 0});
    widget2.Grid({.row = 0, .column = 0});

    MFTK::Tk::AddWindow(mainWindow);
    MFTK::Tk::AddWindow(window2);
    MFTK::Tk::MainLoop();
    delete mainWindow;
    delete window2;
    SDL_Quit();
    return 0;
}