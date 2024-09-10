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
    m_UtfTextIndex { 0 },
    m_TextIndex { 0 },
    m_CaretColor { .r = 220, .g = 220, .b = 220, .a = 255},
    m_CaretBlinkTimer { Timer(800, true, &m_CaretBlinkTimerTimeoutHandler)},
    m_DisplayStartIndex{ 0 }
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

void EntryWidget::InsertText(Sint32 index, const char *text)
{
    index = SetIndex(m_Text, index);
    m_Text.insert(index, text);
}

inline bool IsNotAsciiTextChar(char key)
{
    return key != 0x09 && 
        key != 0x0A &&
        key != 0x0D &&
        (key < 0x20 ||
        key > 0x7E);
}

void EntryWidget::OnBackspace()
{
    if (m_TextIndex > 0)
    {
        if (m_TextIndex > 1 &&
            IsNotAsciiTextChar(m_Text.at(m_TextIndex - 2)) &&
            IsNotAsciiTextChar(m_Text.at(m_TextIndex - 1)))
        {
            m_Text.erase(m_TextIndex - 2, 2);
            m_TextIndex -= 2;
            m_UtfTextIndex--;
        }
        else
        {
            m_Text.erase(m_TextIndex - 1, 1);
            m_UtfTextIndex--;
            m_TextIndex--;
        }
        if (m_UtfTextIndex < m_DisplayStartIndex)
        {
            m_DisplayStartIndex = m_UtfTextIndex;
        }
    }
}

void EntryWidget::OnTextInsert(const char *text)
{
    std::string_view textView = m_Text;

    m_Text.insert(m_TextIndex, text);
    m_UtfTextIndex += SDL_utf8strlen(text);
    m_TextIndex += strlen(text);
    int displaySize = GetDisplaySize();
    if (m_UtfTextIndex > displaySize)
    {
        m_DisplayStartIndex = m_UtfTextIndex - displaySize;
    }
    m_CaretBlinkTimerTimeoutHandler.TurnOn();
    m_CaretBlinkTimer.Start();
}

void EntryWidget::DeleteText(Sint32 index, Uint32 size)
{
    m_CaretBlinkTimerTimeoutHandler.TurnOn();
    m_CaretBlinkTimer.Start();
    index = SetIndex(m_Text, index) - 1;
    if (index >= 0)
    {
        Uint32 removeSize = m_Text.size() - index;
        if (size < removeSize)
        {
            removeSize = size;
        }
        if (index > 0)
        {
            if (IsNotAsciiTextChar(m_Text.at(index - 1)) &&
                IsNotAsciiTextChar(m_Text.at(index)))
            {
                removeSize += 1;
                index -= 1;
            }
        }
        m_Text.erase(index, removeSize);
    }
}

void EntryWidget::ClearText()
{
    m_UtfTextIndex = 0;
    m_TextIndex = 0;
    m_Text.clear();
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
    m_TextIndex = GetTextIndexFromUtf8TextIndex(caretIndex);
    m_UtfTextIndex = caretIndex;
    int displaySize = GetDisplaySize();
    if (m_UtfTextIndex > m_DisplayStartIndex + displaySize)
    {
        m_DisplayStartIndex = m_UtfTextIndex - displaySize;
    }
    else if (m_UtfTextIndex < m_DisplayStartIndex)
    {
        m_DisplayStartIndex = m_UtfTextIndex;
    }
}

Sint32 EntryWidget::GetTextIndexFromUtf8TextIndex(Sint32 utf8TextIndex) const
{
    Sint32 textIndex = 0;
    const size_t textUtfSize = SDL_utf8strlen(m_Text.c_str());
    if (m_Text.size() > 0 && utf8TextIndex <= textUtfSize)
    {
        size_t leftSideUtfLength = SDL_utf8strlen(m_Text.substr(0, utf8TextIndex).c_str());
        int currentIndex = utf8TextIndex;
        for (size_t i = currentIndex; i <= m_Text.size() && leftSideUtfLength <= utf8TextIndex; i++)
        {
            currentIndex++;
            if (currentIndex > m_Text.size())
            {
                break;
            }
            leftSideUtfLength = SDL_utf8strlen(m_Text.substr(0, currentIndex).c_str());
        }
        textIndex = currentIndex - 1;
    }
    else if (m_Text.size() == 0)
    {
        textIndex = 0;
    }
    else
    {
        textIndex = textUtfSize;
    }
    return textIndex;
}


void EntryWidget::RenderWidget()
{
    m_CaretBlinkTimer.Run();
    std::string partialString;
    int utfTextSize = SDL_utf8strlen(m_Text.c_str());
    int displaySize = GetDisplaySize();
    Sint32 displayTextIndex = GetTextIndexFromUtf8TextIndex(m_DisplayStartIndex);
    Sint32 displayLastTextIndex = GetTextIndexFromUtf8TextIndex(utfTextSize);
    if (m_DisplayStartIndex > 0 || utfTextSize > displaySize)
    {
        displayLastTextIndex = GetTextIndexFromUtf8TextIndex(m_DisplayStartIndex + displaySize - 1);
    }
    std::cout << "S: " << displayTextIndex << ", L: " << displayLastTextIndex << ", dS: " << m_DisplayStartIndex << ", size: " << displaySize << "\n";
    partialString = m_Text.substr(displayTextIndex, displayLastTextIndex - displayTextIndex + 1);
    std::string_view stringToDisplay = partialString;

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
        if (m_Text.size() > 0)
        {
            int caretIndex = m_UtfTextIndex - m_DisplayStartIndex;
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
