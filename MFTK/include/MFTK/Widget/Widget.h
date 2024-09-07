#pragma once
#include <SDL.h>
#include "WidgetEventHandler/IWidgetClickedEventHandler.h"
#include "WidgetEventHandler/IWidgetHoverEventHandler.h"
#include "WidgetEventHandler/IWidgetMouseEnterEventHandler.h"
#include "WidgetEventHandler/IWidgetMouseExitEventHandler.h"
#include "WidgetEventHandler/IWidgetKeyPressedEventHandler.h"
#include "WidgetEventHandler/IWidgetKeyReleasedEventHandler.h"
#include "WidgetEventHandler/IWidgetMouseButtonPressedEventHandler.h"
#include "WidgetEventHandler/IWidgetMouseButtonReleasedEventHandler.h"
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

        inline virtual void SetWidgetClickedEventHandler(IWidgetClickedEventHandler *widgetClickedEventHandler)
        {
            m_WidgetClickedEventHandler = widgetClickedEventHandler;
        }

        inline virtual void SetWidgetHoverEventHandler(IWidgetHoverEventHandler *widgetHoverEventHandler)
        {
            m_WidgetHoverEventHandler = widgetHoverEventHandler;
        }

        inline virtual void SetWidgetMouseEnterEventHandler(IWidgetMouseEnterEventHandler *widgetMouseEnterEventHandler)
        {
            m_WidgetMouseEnterEventHandler = widgetMouseEnterEventHandler;
        }

        inline virtual void SetWidgetMouseExitEventHandler(IWidgetMouseExitEventHandler *widgetMouseExitEventHandler)
        {
            m_WidgetMouseExitEventHandler = widgetMouseExitEventHandler;
        }

        inline virtual void SetWidgetKeyPressedEventHandler(IWidgetKeyPressedEventHandler *widgetKeyPressedEventHandler)
        {
            m_WidgetKeyPressedEventHandler = widgetKeyPressedEventHandler;
        }

        inline virtual void SetWidgetKeyReleasedEventHandler(IWidgetKeyReleasedEventHandler *widgetKeyReleasedEventHandler)
        {
            m_WidgetKeyReleasedEventHandler = widgetKeyReleasedEventHandler;
        }

        inline virtual void SetWidgetMouseButtonPressedEventHandler(IWidgetMouseButtonPressedEventHandler *widgetMouseButtonPressedEventHandler)
        {
            m_WidgetMouseButtonPressedEventHandler = widgetMouseButtonPressedEventHandler;
        }

        inline virtual void SetWidgetMouseButtonReleasedEventHandler(IWidgetMouseButtonReleasedEventHandler *widgetMouseButtonReleasedEventHandler)
        {
            m_WidgetMouseButtonReleasedEventHandler = widgetMouseButtonReleasedEventHandler;
        }

        inline void SetBgColor(SDL_Color bgColor) {
            m_BgColor.r = bgColor.r;
            m_BgColor.g = bgColor.g;
            m_BgColor.b = bgColor.b,
            m_BgColor.a = bgColor.a;
        }

        inline void SetBorderColor(SDL_Color borderColor) {
            m_BorderColor.r = borderColor.r;
            m_BorderColor.g = borderColor.g;
            m_BorderColor.b = borderColor.b,
            m_BorderColor.a = borderColor.a;
        }

        inline void SetPadX(int padx) { m_PadX = padx; }
        inline void SetPadY(int pady) { m_PadY = pady; }

        Uint32 GetWidgetID() const;
        bool IsFocused() const { return m_bIsFocused; }
        int GetPadX() const { return m_PadX; }
        int GetPadY() const { return m_PadY; }

    protected:
        virtual void HandleEvents(const SDL_Event *event);
        virtual void Render();

        SDL_Window *GetWindow() const;
        SDL_Renderer *GetRenderer() const;

    protected:
        Window *m_Window;
        SDL_Rect m_Position;
        bool m_bIsHover;
        bool m_bIsFocused;
        static constexpr const Uint32 MOUSE_BUTTON_COUNT = 3;
        Sint32 m_MousePressedState[MOUSE_BUTTON_COUNT];
        IWidgetClickedEventHandler *m_WidgetClickedEventHandler;
        IWidgetHoverEventHandler *m_WidgetHoverEventHandler;
        IWidgetMouseEnterEventHandler *m_WidgetMouseEnterEventHandler;
        IWidgetMouseExitEventHandler *m_WidgetMouseExitEventHandler;
        IWidgetKeyPressedEventHandler *m_WidgetKeyPressedEventHandler;
        IWidgetKeyReleasedEventHandler *m_WidgetKeyReleasedEventHandler;
        IWidgetMouseButtonPressedEventHandler *m_WidgetMouseButtonPressedEventHandler;
        IWidgetMouseButtonReleasedEventHandler *m_WidgetMouseButtonReleasedEventHandler;
        SDL_Color m_BgColor;
        SDL_Color m_BorderColor;
        int m_PadX;
        int m_PadY;

    private:

        void SetWidgetWindow(Window* window);
        Uint32 m_ID;
        friend class Window;


    };
} // namespace MFTK