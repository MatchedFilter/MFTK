#include "MFTK/Widget/EntryWidget/EntryWidget.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseButtonPressedEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseEnterEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetMouseExitEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetKeyPressedEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetTextInputEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetOnFocusOnEventHandler.h"
#include "MFTK/Widget/EntryWidget/EventHandler/EntryWidgetOnFocusOutEventHandler.h"
#include "MFTK/ResourceManager/ResourceManager.h"
#include "MFTK/Common/Time/Timer.h"
#include <iostream>
#include <cstring>
#include "MFTK/Common/Utils/UtfConverter.h"

using namespace MFTK;

EntryWidget::EntryWidget(Window *window, Sint32 w, Sint32 h, FontData fontData) :
    Widget { window, w, h},
    m_bIsMouseButtonPressedEventUpdated { false },
    m_bIsMouseEnterEventUpdated { false },
    m_bIsMouseExitEventUpdated { false },
    m_bIsKeyPressedEventUpdated { false },
    m_bIsTextInputEventUpdated { false },
    m_Font { nullptr },
    m_FgColor { .r = 200, .g = 200, .b = 200, .a = 255 },
    m_Utf32TextIndex { 0 },
    m_CaretColor { .r = 220, .g = 220, .b = 220, .a = 255},
    m_CaretBlinkTimer { Timer(800, true, &m_CaretBlinkTimerTimeoutHandler)},
    m_DisplayStartIndex{ 0 },
    m_SelectedRange { 0, 0 }
{
    m_WidgetMouseButtonPressedEventHandler = new EntryWidgetMouseButtonPressedEventHandler();
    m_WidgetMouseEnterEventHandler = new EntryWidgetMouseEnterEventHandler();
    m_WidgetMouseExitEventHandler = new EntryWidgetMouseExitEventHandler();
    m_WidgetKeyPressedEventHandler = new EntryWidgetKeyPressedEventHandler();
    m_WidgetTextInputEventHandler = new EntryWidgetTextInputEventHandler();
    m_WidgetOnFocusOnEventHandler = new EntryWidgetOnFocusOnEventHandler();
    m_WidgetOnFocusOutEventHandler = new EntryWidgetOnFocusOutEventHandler();
    m_Font = ResourceManager::CreateFont(fontData);
}

EntryWidget::~EntryWidget()
{
}

void EntryWidget::SetWidgetMouseButtonPressedEventHandler(IWidgetMouseButtonPressedEventHandler *widgetMouseButtonPressedEventHandler)
{
    Widget::SetWidgetMouseButtonPressedEventHandler(widgetMouseButtonPressedEventHandler);
    m_bIsMouseButtonPressedEventUpdated = true;
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
    Widget::SetWidgetKeyPressedEventHandler(widgetKeyPressedEventHandler);
    m_bIsKeyPressedEventUpdated = true;
}

void EntryWidget::SetWidgetTextInputEventHandler(IWidgetTextInputEventHandler *widgetTextInputEventHandler)
{
    Widget::SetWidgetTextInputEventHandler(widgetTextInputEventHandler);
    m_bIsTextInputEventUpdated = true;
}

void EntryWidget::SetWidgetOnFocusOnEventHandler(IWidgetOnFocusOnEventHandler *widgetOnFocusOnEventHandler)
{
    Widget::SetWidgetOnFocusOnEventHandler(widgetOnFocusOnEventHandler);
    m_bIsFocusOnEventUpdated = true;
}

void EntryWidget::SetWidgetOnFocusOutEventHandler(IWidgetOnFocusOutEventHandler *widgetOnFocusOutEventHandler)
{
    Widget::SetWidgetOnFocusOutEventHandler(widgetOnFocusOutEventHandler);
    m_bIsFocusOutEventUpdated = true;
}

inline Sint32 SetIndex(const std::string &text, Sint32 index)
{
    if (index < 0)
    {
        index = text.size() + index + 1;
        if (index < 0)
        {
            index = 0;
        }
    }
    else if (index > text.size())
    {
        index = text.size();
    }
    return index;
}

void EntryWidget::InsertText(Sint32 index,std::u32string_view text)
{
    m_Utf32String.insert(index, text);
}

void EntryWidget::OnBackspace()
{
    if (m_Utf32TextIndex > 0)
    {
        m_Utf32String.erase(m_Utf32TextIndex - 1, 1);
        m_Utf32TextIndex--;
        if (m_Utf32TextIndex < m_DisplayStartIndex)
        {
            m_DisplayStartIndex = m_Utf32TextIndex;
        }
    }
}

void EntryWidget::OnTextInsert(std::u32string_view text)
{
    m_Utf32String.insert(m_Utf32TextIndex, text);
    m_Utf32TextIndex += text.size();
    int displaySize = GetDisplaySize();
    if (m_Utf32TextIndex > displaySize)
    {
        m_DisplayStartIndex = m_Utf32TextIndex - displaySize;
    }
    m_CaretBlinkTimerTimeoutHandler.TurnOn();
    m_CaretBlinkTimer.Start();
}

void EntryWidget::DeleteText(Sint32 index, Uint32 size)
{
    m_CaretBlinkTimerTimeoutHandler.TurnOn();
    m_CaretBlinkTimer.Start();
    
    if (index >= 0)
    {

        Uint32 removeSize = m_Utf32String.size() - index;
        if (size < removeSize)
        {
            removeSize = size;
        }

        m_Utf32String.erase(index, removeSize);
    }
}

void EntryWidget::ClearText()
{
    m_Utf32TextIndex = 0;
    m_Utf32String.clear();
}

int EntryWidget::GetPixelPerChar() const
{
    int textW, textH;
    TTF_SizeUTF8(m_Font, "a", &textW, &textH);
    return textW;
}

int EntryWidget::GetDisplaySize() const
{
    constexpr const int32_t CLEARANCE_PADX_PIXEL = 2;
    return static_cast<int>(static_cast<double>(m_Position.w - 2 * m_PadX + CLEARANCE_PADX_PIXEL) / GetPixelPerChar());
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
        if (!m_bIsKeyPressedEventUpdated)
        {
            delete m_WidgetKeyPressedEventHandler;
            m_WidgetKeyPressedEventHandler = nullptr;
        }
    }

    if (m_WidgetTextInputEventHandler != nullptr)
    {
        if (!m_bIsTextInputEventUpdated)
        {
            delete m_WidgetTextInputEventHandler;
            m_WidgetTextInputEventHandler = nullptr;
        }
    }

    if (m_WidgetOnFocusOnEventHandler != nullptr)
    {
        if (!m_bIsFocusOnEventUpdated)
        {
            delete m_WidgetOnFocusOnEventHandler;
            m_WidgetOnFocusOnEventHandler = nullptr;
        }
    }

    if (m_WidgetOnFocusOutEventHandler != nullptr)
    {
        if (!m_bIsFocusOutEventUpdated)
        {
            delete m_WidgetOnFocusOutEventHandler;
            m_WidgetOnFocusOutEventHandler = nullptr;
        }
    }

    if (m_WidgetMouseButtonPressedEventHandler != nullptr)
    {
        if (!m_bIsMouseButtonPressedEventUpdated)
        {
            delete m_WidgetMouseButtonPressedEventHandler;
            m_WidgetMouseButtonPressedEventHandler = nullptr;
        }
    }
}

void EntryWidget::SetCaretIndex(Sint32 caretIndex)
{
    m_Utf32TextIndex = caretIndex;
    int displaySize = GetDisplaySize();
    if (m_Utf32TextIndex > m_DisplayStartIndex + displaySize)
    {
        m_DisplayStartIndex = m_Utf32TextIndex - displaySize;
    }
    else if (m_Utf32TextIndex < m_DisplayStartIndex)
    {
        m_DisplayStartIndex = m_Utf32TextIndex;
    }
}

void EntryWidget::RenderWidget()
{
    m_CaretBlinkTimer.Run();
    std::u32string partialString;
    int displaySize = GetDisplaySize();
    Sint32 displayTextIndex = m_DisplayStartIndex;
    Sint32 displayLastTextIndex = m_Utf32String.size();
    if (m_DisplayStartIndex > 0 || displayLastTextIndex > displaySize)
    {
        displayLastTextIndex = m_DisplayStartIndex + displaySize - 1;
    }
    partialString = m_Utf32String.substr(m_DisplayStartIndex, displayLastTextIndex - m_DisplayStartIndex + 1);
    std::string stringToDisplay = UtfConverter::ConvertFromUtf32ToUtf8(partialString);

    int textW, textH;
    TTF_SizeUTF8(m_Font, stringToDisplay.data(), &textW, &textH);
    if (m_Position.h < textH + 2 * m_PadY)
    {
        m_Position.h = textH + 2 * m_PadY;
    }
    
    int textHOffset = (m_Position.h - textH) / 2;
    SDL_Rect textRect = {.x = m_Position.x + m_PadX + 1, .y = m_Position.y + textHOffset, .w = textW, .h = textH };

    if (m_CaretBlinkTimerTimeoutHandler.IsTurnedOn())
    {
        int caretXPos =  m_Position.x + m_PadX + 1;
        if (m_Utf32String.size() > 0)
        {
            int caretIndex = m_Utf32TextIndex - m_DisplayStartIndex;
            caretXPos += static_cast<int>(caretIndex * GetPixelPerChar());
        }
        SDL_Rect caretRect = {.x = caretXPos,
            .y = m_Position.y + textHOffset,
            .w = 1, .h = textH };
        SDL_SetRenderDrawColor(Widget::GetRenderer(), m_CaretColor.r, m_CaretColor.g, m_CaretColor.b, m_CaretColor.a);
        SDL_RenderDrawRect(Widget::GetRenderer(), &caretRect);
    }

    SDL_Surface *surfaceText = TTF_RenderUTF8_Blended(m_Font , stringToDisplay.data(), m_FgColor);
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(Widget::GetRenderer(), surfaceText);
    SDL_FreeSurface(surfaceText);
    
    SDL_RenderCopy(Widget::GetRenderer(), textureText, NULL, &textRect);
    SDL_DestroyTexture(textureText);
}
