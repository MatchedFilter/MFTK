#pragma once
#include <SDL.h>
#include "WindowEventHandler/IWindowClosedEventHandler.h"
#include "MFTK/Widget/Widget.h"
#include "MFTK/Common/GridData.h"
#include <map>

namespace MFTK
{
    class Window
    {
    public:
        Window(Sint32 width, Sint32 height, const char *title);
        ~Window();


        void SetFps(Uint32 fps) { m_Fps = fps; }
        void SetBgColor(SDL_Color bgColor) {
            m_BgColor.r = bgColor.r;
            m_BgColor.g = bgColor.g;
            m_BgColor.b = bgColor.b,
            m_BgColor.a = bgColor.a;
        }
        void SetWindowClosedEventHandler(IWindowClosedEventHandler *windowClosedEventHandler)
        {
            m_WindowClosedEventHandler = windowClosedEventHandler;
        }

    protected:
        void HandleEvents(const SDL_Event *event);
        void Render();

    private:
        Sint32 m_Width;
        Sint32 m_Height;
        const char *m_Title;
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
        Uint32 m_ID;
        Uint32 m_Fps;
        SDL_Color m_BgColor;
        IWindowClosedEventHandler *m_WindowClosedEventHandler;
        std::map<Uint32, Widget*, std::greater<Uint32>> m_WidgetMap; 
        std::map<Sint32, Sint32> m_RowMap;
        std::map<Sint32, Sint32> m_ColumnMap;

        friend class Tk;
        friend class Widget;

    private:
        void Destroy();
        void RegisterWidget(Widget *widget);
        void UnregisterWidget(Uint32 widgetID);
        void GridWidget(Widget *widget, GridData gridData);
    };
} // namespace MFTK

