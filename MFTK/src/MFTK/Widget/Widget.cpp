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

static constexpr Uint8 BUTTON_LEFT = 0;
static constexpr Uint8 BUTTON_MIDDLE = 1;
static constexpr Uint8 BUTTON_RIGHT = 2;
inline Uint8 GetButtonCode(const SDL_Event* event)
{
    Uint8 buttonCode = BUTTON_LEFT;
    switch (event->button.button)
    {
    case SDL_BUTTON_LEFT:
        buttonCode = BUTTON_LEFT;
        break;
    case SDL_BUTTON_RIGHT:
        buttonCode = BUTTON_RIGHT;
        break;
    case SDL_BUTTON_MIDDLE:
        buttonCode = BUTTON_MIDDLE;
        break;
    
    default:
        break;
    }
    return buttonCode;
}


Widget::Widget(Window *window, Sint32 w, Sint32 h) :
    m_Window { window },
    m_Position { .x = 0, .y = 0, .w = w, .h = h },
    m_bIsHover { false },
    m_bIsFocused { false },
    m_MousePressedState { SDL_MOUSEBUTTONUP },
    m_WidgetClickedEventHandler { nullptr },
    m_WidgetHoverEventHandler { nullptr },
    m_WidgetMouseEnterEventHandler { nullptr },
    m_WidgetMouseExitEventHandler { nullptr },
    m_WidgetKeyPressedEventHandler { nullptr },
    m_WidgetKeyReleasedEventHandler { nullptr },
    m_WidgetMouseButtonPressedEventHandler { nullptr },
    m_WidgetMouseButtonReleasedEventHandler { nullptr },
    m_BgColor { .r = 40, .g = 40, .b = 40, .a = 255 },
    m_BorderColor { .r = 160, .g = 160, .b = 180, .a = 255 },
    m_PadX { 1 },
    m_PadY { 1 },
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
            if (m_WidgetMouseEnterEventHandler != nullptr)
            {
                m_WidgetMouseEnterEventHandler->OnEnter(this, event);
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
            if (m_WidgetMouseExitEventHandler != nullptr)
            {
                m_WidgetMouseExitEventHandler->OnExit(this, event);
            }
        }
        m_bIsHover = false;
    }

    switch (event->type)
    {
    case SDL_MOUSEBUTTONUP:
    {
        Uint8 buttonCode = GetButtonCode(event);
        if (m_bIsHover)
        {
            if (m_MousePressedState[buttonCode] != SDL_MOUSEBUTTONUP)
            {
                if (m_WidgetMouseButtonReleasedEventHandler != nullptr)
                {
                    m_WidgetMouseButtonReleasedEventHandler->OnMouseButtonReleased(this, event);
                }
            }
            if (m_MousePressedState[buttonCode] == SDL_MOUSEBUTTONDOWN)
            {
                if (m_WidgetClickedEventHandler != nullptr)
                {
                    m_WidgetClickedEventHandler->OnWidgetClicked(this, event);
                    m_bIsFocused = true;
                }
            }
        }
        else
        {
            m_bIsFocused = false;
        }
        m_MousePressedState[buttonCode] = SDL_MOUSEBUTTONUP;
    }
    break;

    case SDL_MOUSEBUTTONDOWN:
    {
        Uint8 buttonCode = GetButtonCode(event);
        if (m_bIsHover)
        {
            if (m_MousePressedState[buttonCode] != SDL_MOUSEBUTTONDOWN)
            {
                if (m_WidgetMouseButtonPressedEventHandler != nullptr)
                {
                    m_WidgetMouseButtonPressedEventHandler->OnMouseButtonPressed(this, event);
                }
            }
            m_MousePressedState[buttonCode] = SDL_MOUSEBUTTONDOWN;
        }
    }
    break;

    case SDL_KEYDOWN:
    {
        if (m_WidgetKeyPressedEventHandler != nullptr)
        {
            m_WidgetKeyPressedEventHandler->OnKeyPressed(this, event);
        }
    }
    break;

    case SDL_KEYUP:
    {
        if (m_WidgetKeyReleasedEventHandler != nullptr)
        {
            m_WidgetKeyReleasedEventHandler->OnKeyReleased(this, event);
        }
    }
    break;

    
    default:
        break;
    }

    if (event->type == SDL_KEYDOWN)
    {

    }
}

void Widget::Render()
{
    if (m_Window == nullptr)
    {
        throw NullWindowException();
    }
    SDL_SetRenderDrawColor(m_Window->m_Renderer, m_BorderColor.r, m_BorderColor.g, m_BorderColor.b, m_BorderColor.a);
    SDL_RenderFillRect(m_Window->m_Renderer, &m_Position);
    SDL_SetRenderDrawColor(m_Window->m_Renderer, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_Rect insideRect = { .x = m_Position.x + m_PadX, .y = m_Position.y + m_PadY, .w = (m_Position.w - 2 * m_PadX), .h = (m_Position.h - 2 * m_PadY) };
    SDL_RenderFillRect(m_Window->m_Renderer, &insideRect);
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
