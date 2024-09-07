#include "MFTK/Tk.h"
#include "MFTK/Widget/EntryWidget/EntryWidget.h"

int main(int argc, char *argv[])
{
    MFTK::Tk::Initialize(120);
 
    
    MFTK::Window *mainWindow = new MFTK::Window(800, 600, "Main Window");
    mainWindow->SetBgColor({.r = 20, .g = 20, .b = 20, .a = 255});

    MFTK::EntryWidget *entry1 = new MFTK::EntryWidget(mainWindow, 80, 25);
    entry1->InsertText(0, "Hello");
    entry1->InsertText(-1, " World");
    entry1->Grid({.row = 0, .column = 0});

    MFTK::Tk::AddWindow(mainWindow);
    MFTK::Tk::MainLoop();

    delete mainWindow;
    SDL_Quit();
    return 0;
}