#pragma once
#include <SDL.h>
#include "WidgetEventHandler/IWidgetClickedEventHandler.h"
#include "WidgetEventHandler/IWidgetHoverEventHandler.h"
#include "WidgetEventHandler/IWidgetEnterEventHandler.h"
#include "WidgetEventHandler/IWidgetExitEventHandler.h"
#include "MFTK/Common/GridData.h"

namespace MFTK
{
    class Window;
    class Widget
    {
    public:
        Widget(Window *window, Sint32 w, Sint32 h);
        virtual ~Widget();
        virtual void Destroy();
        void Grid(GridData gridData);
        void SetWidgetClickedEventHandler(IWidgetClickedEventHandler *widgetClickedEventHandler)
        {
            m_WidgetClickedEventHandler = widgetClickedEventHandler;
        }
        void SetWidgetHoverEventHandler(IWidgetHoverEventHandler *widgetHoverEventHandler)
        {
            m_WidgetHoverEventHandler = widgetHoverEventHandler;
        }
        void SetWidgetEnterEventHandler(IWidgetEnterEventHandler *widgetEnterEventHandler)
        {
            m_WidgetEnterEventHandler = widgetEnterEventHandler;
        }
        void SetWidgetExitEventHandler(IWidgetExitEventHandler *widgetExitEventHandler)
        {
            m_WidgetExitEventHandler = widgetExitEventHandler;
        }

        void SetBgColor(SDL_Color bgColor) {
            m_BgColor.r = bgColor.r;
            m_BgColor.g = bgColor.g;
            m_BgColor.b = bgColor.b,
            m_BgColor.a = bgColor.a;
        }

        Uint32 GetWidgetID() const;

    protected:
        virtual void HandleEvents(const SDL_Event *event);
        virtual void Render();

    private:
        Window *m_Window;
        SDL_Rect m_Position;
        bool m_bIsHover;
        Sint32 m_MousePressedState;
        IWidgetClickedEventHandler *m_WidgetClickedEventHandler;
        IWidgetHoverEventHandler *m_WidgetHoverEventHandler;
        IWidgetEnterEventHandler *m_WidgetEnterEventHandler;
        IWidgetExitEventHandler *m_WidgetExitEventHandler;
        SDL_Color m_BgColor;

    private:

        void SetWidgetWindow(Window* window);
        Uint32 m_ID;
        friend class Window;


    };
} // namespace MFTK