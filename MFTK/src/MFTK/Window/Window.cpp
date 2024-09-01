#include "MFTK/Window/Window.h"
#include "MFTK/Tk.h"
#include <list>

using namespace MFTK;


Window::Window(Sint32 width, Sint32 height, const char *title) : 
    m_Width { width }, m_Height { height },
    m_Title { title }, m_Window { nullptr },
    m_Renderer { nullptr }, m_ID { 0 }, m_Fps { 0 },
    m_WindowClosedEventHandler { nullptr }
{
}

Window::~Window()
{
    Destroy();
}

void Window::HandleEvents(const SDL_Event *event)
{
    if (event->window.windowID == m_ID)
    {
        for (auto &widget_pair: m_WidgetMap)
        {
            auto &widget = widget_pair.second;
            widget->HandleEvents(event);
        }
    }
}

void Window::Render()
{
    SDL_RenderClear(m_Renderer);
    for (auto &widget_pair: m_WidgetMap)
    {
        auto &widget = widget_pair.second;
        widget->Render();
    }
    SDL_SetRenderDrawColor(m_Renderer, m_BgColor.r, m_BgColor.g, m_BgColor.b, m_BgColor.a);
    SDL_RenderPresent(m_Renderer);
}

void Window::Destroy()
{
    std::list<Uint32> widgetIDList;
    for (auto &widget_pair: m_WidgetMap)
    {
        widgetIDList.push_back(widget_pair.first);
    }
    for (auto &widgetID : widgetIDList)
    {
        m_WidgetMap[widgetID]->Destroy();
    }
    if (m_WindowClosedEventHandler != nullptr)
    {
        m_WindowClosedEventHandler->OnWindowClosed();
    }
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    m_Renderer = nullptr;
}

void Window::RegisterWidget(Widget *widget)
{
    m_WidgetMap[widget->GetWidgetID()] = widget;
}

void Window::UnregisterWidget(Uint32 widgetID)
{
    if (m_WidgetMap.find(widgetID) != m_WidgetMap.end())
    {
        m_WidgetMap.erase(widgetID);
    }
}

void Window::GridWidget(Widget *widget, GridData gridData)
{
    if (m_RowMap.find(gridData.row) != m_RowMap.end())
    {
        Sint32 rowWidth = m_RowMap[gridData.row];
        if (rowWidth < widget->m_Position.h)
        {
            m_RowMap[gridData.row] = widget->m_Position.h;
        }
    }
    else
    {
        m_RowMap[gridData.row] = widget->m_Position.h;
    }

    if (m_ColumnMap.find(gridData.column) != m_ColumnMap.end())
    {
        Sint32 columnWidth = m_ColumnMap[gridData.column];
        if (columnWidth < widget->m_Position.w)
        {
            m_RowMap[gridData.column] = widget->m_Position.w;
        }
    }
    else
    {
        m_ColumnMap[gridData.row] = widget->m_Position.w;;
    }


    Sint32 x = 0;
    Sint32 y = 0;
    for (const auto &it: m_RowMap)
    {
        if (it.first == gridData.row)
        {
            break;
        }
        else
        {
            y += it.second;
        }
    }

    for (const auto &it: m_ColumnMap)
    {
        if (it.first == gridData.column)
        {
            break;
        }
        else
        {
            x += it.second;
        }
    }

    widget->m_Position.x = x;
    widget->m_Position.y = y;
}

