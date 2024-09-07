#pragma once
#include "MFTK/Widget/Widget.h"
#include <SDL_ttf.h>
#include "MFTK/ResourceManager/FontData.h"
#include <string>

namespace MFTK
{
    class EntryWidget: public Widget
    {
    public:
        EntryWidget(Window *window, Sint32 w, Sint32 h, FontData fontData = {.font = "JetBrains Mono", .size = 15});
        virtual ~EntryWidget();
        virtual void Destroy() override;

        virtual void SetWidgetMouseEnterEventHandler(IWidgetMouseEnterEventHandler *widgetMouseEnterEventHandler) override;
        virtual void SetWidgetMouseExitEventHandler(IWidgetMouseExitEventHandler *widgetMouseExitEventHandler) override;
        virtual void SetWidgetKeyPressedEventHandler(IWidgetKeyPressedEventHandler *widgetKeyPressedEventHandler) override;

        void InsertText(int32_t index, const char *text);

        // Getters
        const char *GetText() const { return m_Text.c_str(); }

        // Setters
        inline void SetFgColor(SDL_Color fgColor) {
            m_FgColor.r = fgColor.r;
            m_FgColor.g = fgColor.g;
            m_FgColor.b = fgColor.b,
            m_FgColor.a = fgColor.a;
        }


    protected:
        virtual void Render() override;

    private:
        bool m_bIsMouseEnterEventUpdated;
        bool m_bIsMouseExitEventUpdated;
        bool m_bIsKeyPressedEventUpdate;

        std::string m_Text;
        TTF_Font *m_Font;
        SDL_Color m_FgColor;
    };
    
} // namespace MFTK
