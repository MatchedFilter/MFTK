#pragma once
#include "MFTK/Widget/Widget.h"
#include <SDL_ttf.h>
#include "MFTK/ResourceManager/FontData.h"
#include "TimerHandler/CaretBlinkTimerTimeoutHandler.h"
#include "MFTK/Common/Time/Timer.h"
#include <string>

namespace MFTK
{
    class EntryWidget: public Widget
    {
    public:
        EntryWidget(Window *window, Sint32 w, Sint32 h, FontData fontData = {.font = "JetBrains Mono", .size = 15});
        virtual ~EntryWidget();
        virtual void Destroy() override;

        virtual void SetWidgetMouseButtonPressedEventHandler(IWidgetMouseButtonPressedEventHandler *widgetMouseButtonPressedEventHandler) override;
        virtual void SetWidgetMouseEnterEventHandler(IWidgetMouseEnterEventHandler *widgetMouseEnterEventHandler) override;
        virtual void SetWidgetMouseExitEventHandler(IWidgetMouseExitEventHandler *widgetMouseExitEventHandler) override;
        virtual void SetWidgetKeyPressedEventHandler(IWidgetKeyPressedEventHandler *widgetKeyPressedEventHandler) override;
        virtual void SetWidgetTextInputEventHandler(IWidgetTextInputEventHandler *widgetTextInputEventHandler) override;
        virtual void SetWidgetOnFocusOnEventHandler(IWidgetOnFocusOnEventHandler *widgetOnFocusOnEventHandler) override;
        virtual void SetWidgetOnFocusOutEventHandler(IWidgetOnFocusOutEventHandler *widgetOnFocusOutEventHandler) override;

        void InsertText(Sint32 index, const char *text);
        void DeleteText(Sint32 index, Uint32 size);
        void ClearText();
        int GetPixelPerChar() const;
        int GetDisplaySize() const;

        // Getters
        const char *GetText() const { return m_Text.c_str(); }

        inline Sint32 GetCaretIndex() const { return m_UtfTextIndex; }
        inline Sint32 GetDisplayStartIndex() const { return m_DisplayStartIndex; }

        // Setters
        inline void SetFgColor(SDL_Color fgColor) {
            m_FgColor.r = fgColor.r;
            m_FgColor.g = fgColor.g;
            m_FgColor.b = fgColor.b,
            m_FgColor.a = fgColor.a;
        }

        inline void SetCaretColor(SDL_Color caretColor) {
            m_CaretColor.r = caretColor.r;
            m_CaretColor.g = caretColor.g;
            m_CaretColor.b = caretColor.b,
            m_CaretColor.a = caretColor.a;
        }

        void SetCaretIndex(Sint32 caretIndex);

    protected:
        Sint32 GetTextIndexFromUtf8TextIndex(Sint32 textIndex) const;
        virtual void RenderWidget() override;
        virtual void OnBackspace();
        virtual void OnTextInsert(const char *text);


    private:
        bool m_bIsMouseButtonPressedEventUpdated;
        bool m_bIsMouseEnterEventUpdated;
        bool m_bIsMouseExitEventUpdated;
        bool m_bIsKeyPressedEventUpdated;
        bool m_bIsTextInputEventUpdated;
        bool m_bIsFocusOnEventUpdated;
        bool m_bIsFocusOutEventUpdated;

        std::string m_Text;
        TTF_Font *m_Font;
        SDL_Color m_FgColor;
        Sint32 m_UtfTextIndex;
        Sint32 m_TextIndex;
        SDL_Color m_CaretColor;
        CaretBlinkTimerTimeoutHandler m_CaretBlinkTimerTimeoutHandler;
        Timer m_CaretBlinkTimer;
        Sint32 m_DisplayStartIndex;

        friend class EntryWidgetOnFocusOnEventHandler;
        friend class EntryWidgetOnFocusOutEventHandler;
        friend class EntryWidgetKeyPressedEventHandler;
        friend class EntryWidgetTextInputEventHandler;
    };
    
} // namespace MFTK
