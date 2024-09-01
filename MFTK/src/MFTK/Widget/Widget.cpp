#include "MFTK/Widget/Widget.h"
#include "MFTK/Window/Window.h"
#include "MFTK/Tk.h"
#include "MFTK/Exceptions/NullWindowException.h"
#include "MFTK/Exceptions/WidgetNotAddedToWindowException.h"

using namespace MFTK;

inline bool IsInHorizantalRange(const SDL_Event *event, const SDL_Rect &position)
{
    return (event->motion.x > position.x) && 
        (event->motion.x < position.x + position.w);
}

inline bool IsInVerticalRange(const SDL_Event *event, const SDL_Rect &position)
{
    return (event->motion.y > position.y) && 
        (event->motion.y < position.y + position.h);
}


Widget::Widget(Window *window, Sint32 w, Sint32 h) :
    m_Window { window },
    m_Position { .x = 0, .y = 0, .w = w, .h = h },
    m_bIsHover { false },
    m_MousePressedState { SDL_MOUSEBUTTONUP },
    m_WidgetClickedEventHandler { nullptr },
    m_WidgetHoverEventHandler { nullptr },
    m_WidgetEnterEventHandler { nullptr },
    m_WidgetExitEventHandler { nullptr },
    m_BgColor { .r = 100, .g = 100, .b = 100, .a = 255 },
    m_ID { 0 }
{
    m_ID = Tk::GenerateWidgetID();
    m_Window->RegisterWidget(this);
}

Widget::~Widget()
{
    Destroy();
}

void Widget::HandleEvents(const SDL_Event *event)
{
    if (IsInHorizantalRange(event, m_Position) && 
        IsInVerticalRange(event, m_Position))
    {
        if (m_bIsHover == false)
        {
            if (m_WidgetEnterEventHandler != nullptr)
            {
                m_WidgetEnterEventHandler->OnEnter(this, event);
            }
        }
        if (m_WidgetHoverEventHandler != nullptr)
        {
            m_WidgetHoverEventHandler->OnHover(this, event);
        }
        m_bIsHover = true;
    }
    else
    {
        if (m_bIsHover == true)
        {
            if (m_WidgetExitEventHandler != nullptr)
            {
                m_WidgetExitEventHandler->OnExit(this, event);
            }
        }
        m_bIsHover = false;
    }

    if (event->type == SDL_MOUSEBUTTONUP)
    {
        if (
            m_MousePressedState == SDL_MOUSEBUTTONDOWN &&
            m_bIsHover
        )
        {
            if (m_WidgetClickedEventHandler != nullptr)
            {
                m_WidgetClickedEventHandler->OnWidgetClicked(this, event);
            }
        }
        m_MousePressedState = SDL_MOUSEBUTTONUP;
    }
    else if (m_bIsHover &&
        event->type == SDL_MOUSEBUTTONDOWN)
    {
        m_MousePressedState = SDL_MOUSEBUTTONDOWN;
    }
}

void Widget::Render()
{
    if (m_Window == nullptr)
    {
        throw NullWindowException();
    }
    SDL_SetRenderDrawColor(m_Window->m_Renderer, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_RenderDrawRect(m_Window->m_Renderer, &m_Position);
    SDL_SetRenderDrawColor(m_Window->m_Renderer, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_RenderFillRect(m_Window->m_Renderer, &m_Position);
}

void Widget::Destroy()
{
    if (m_Window !=  nullptr)
    {
        m_Window->UnregisterWidget(this->m_ID);
    }
    m_ID = 0;
    m_Window = nullptr;
}

void Widget::Grid(GridData gridData)
{
    m_Window->GridWidget(this, gridData);
}


Uint32 Widget::GetWidgetID() const
{
    if (m_ID == 0)
    {
        throw WidgetNotAddedToWindowException();
    }
    return m_ID;
}


void Widget::SetWidgetWindow(Window* window)
{
    m_Window = window;
}
