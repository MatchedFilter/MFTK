#pragma once
#include "MFTK/Window/Window.h"

namespace MFTK
{
    class Tk
    {
    public:
        Tk() = delete;
        static void Initialize(Uint32 fps = 0);
        static void AddWindow(Window *window);
        static void DestroyApplication();
        static void MainLoop();

    private:
        static void HandleMainEvents(SDL_Event *event);
        static void DestroyWindow(Window *window);
        friend class Window;
        friend class Widget;
        static Uint32 GenerateWidgetID();
        static Uint32 s_Fps;

    };
} // namespace MFTK
