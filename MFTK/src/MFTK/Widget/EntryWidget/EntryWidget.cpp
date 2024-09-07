#include "MFTK/Widget/EntryWidget/EntryWidget.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseEnterEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseExitEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetKeyPressedEventHandler.h"
#include "MFTK/ResourceManager/ResourceManager.h"
#include <iostream>

using namespace MFTK;

EntryWidget::EntryWidget(Window *window, Sint32 w, Sint32 h, FontData fontData) :
    Widget { window, w, h},
    m_bIsMouseEnterEventUpdated { false },
    m_bIsMouseExitEventUpdated { false },
    m_bIsKeyPressedEventUpdate { false },
    m_Font { nullptr },
    m_FgColor { .r = 200, .g = 200, .b = 200 }
{
    m_WidgetMouseEnterEventHandler = new EntryWidgetMouseEnterEventHandler();
    m_WidgetMouseExitEventHandler = new EntryWidgetMouseExitEventHandler();
    m_WidgetKeyPressedEventHandler = new EntryWidgetKeyPressedEventHandler();
    m_Font = ResourceManager::CreateFont(fontData);
}

EntryWidget::~EntryWidget()
{
}

void EntryWidget::SetWidgetMouseEnterEventHandler(IWidgetMouseEnterEventHandler *widgetMouseEnterEventHandler)
{
    Widget::SetWidgetMouseEnterEventHandler(widgetMouseEnterEventHandler);
    m_bIsMouseEnterEventUpdated = true;
}

void EntryWidget::SetWidgetMouseExitEventHandler(IWidgetMouseExitEventHandler *widgetMouseExitEventHandler)
{
    Widget::SetWidgetMouseExitEventHandler(widgetMouseExitEventHandler);
    m_bIsMouseExitEventUpdated = true;
}

void EntryWidget::SetWidgetKeyPressedEventHandler(IWidgetKeyPressedEventHandler *widgetKeyPressedEventHandler)
{
    Widget::SetWidgetKeyPressedEventHandler(m_WidgetKeyPressedEventHandler);
    m_bIsKeyPressedEventUpdate = true;
}

void EntryWidget::InsertText(int32_t index, const char *text)
{
    if (index < 0)
    {
        index = m_Text.size() + index + 1;
        if (index < 0)
        {
            index = 0;
        }
    }
    else if (index > m_Text.size())
    {
        index = m_Text.size();
    }
    m_Text.insert(index, text);
}

void EntryWidget::Destroy()
{
    if (m_WidgetMouseEnterEventHandler != nullptr)
    {
        if (!m_bIsMouseEnterEventUpdated)
        {
            delete m_WidgetMouseEnterEventHandler;
            m_WidgetMouseEnterEventHandler = nullptr;
        }
    }
    if (m_WidgetMouseExitEventHandler != nullptr)
    {
        if (!m_bIsMouseExitEventUpdated)
        {
            delete m_WidgetMouseEnterEventHandler;
            m_WidgetMouseEnterEventHandler = nullptr;
        }
    }

    if (m_WidgetKeyPressedEventHandler != nullptr)
    {
        if (!m_bIsKeyPressedEventUpdate)
        {
            delete m_WidgetKeyPressedEventHandler;
            m_WidgetKeyPressedEventHandler = nullptr;
        }
    }
}

void EntryWidget::Render()
{
    std::string_view stringToDisplay = m_Text;
    std::string tempString;
    int displaySize = stringToDisplay.size();
    Widget::Render();
    int textW, textH;
    TTF_SizeUTF8(m_Font, stringToDisplay.data(), &textW, &textH);
    if (m_Position.h < textH + 2 * m_PadY)
    {
        m_Position.h = textH + 2 * m_PadY;
    }
    
    
    int textHOffset = (m_Position.h - textH) / 2;
    if (textW > m_Position.w && stringToDisplay.size() > 0)
    {
        constexpr const int32_t CLEARANCE_PADX_PIXEL = 2;
        double pixelPerChar = static_cast<double>(textW) / static_cast<double>(stringToDisplay.size());
        displaySize = static_cast<int>(static_cast<double>(m_Position.w - 2 * m_PadX + CLEARANCE_PADX_PIXEL) / pixelPerChar);
        tempString = stringToDisplay.substr(0, displaySize);
        stringToDisplay = tempString;
        TTF_SizeUTF8(m_Font, stringToDisplay.data(), &textW, &textH);
    }
    SDL_Rect textRect = {.x = m_Position.x + m_PadX + 1, .y = m_Position.y + textHOffset, .w = textW, .h = textH };
    std::cout << "w: " << textW << ", posW: " << m_Position.w << ", h: " << textH << ", posH: " << m_Position.h << "\n";

    SDL_Surface *surfaceText = TTF_RenderUTF8_Blended(m_Font , stringToDisplay.data(), m_FgColor);
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(Widget::GetRenderer(), surfaceText);
    SDL_FreeSurface(surfaceText);
    SDL_RenderCopy(Widget::GetRenderer(), textureText, NULL, &textRect);
    SDL_DestroyTexture(textureText);
}
