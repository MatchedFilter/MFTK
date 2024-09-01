#pragma once
#include "MFTK/Tk.h"
#include "MFTK/Widget/WidgetEventHandler/IWidgetClickedEventHandler.h"
#include <iostream>
#include <string>

class OnMouseClickedEventHandler : public MFTK::IWidgetClickedEventHandler
{
public:
    OnMouseClickedEventHandler() = default;
    ~OnMouseClickedEventHandler() = default;
    virtual void OnWidgetClicked(MFTK::Widget *widget, const SDL_Event *event) override
    {
        std::cout << "Clicked on widget: " << widget->GetWidgetID() << ",  with: [" << GetText(event->button.button) << "]" << std::endl;
    }

private:
    static std::string_view GetText(int buttonID)
    {
        switch (buttonID)
        {
        case SDL_BUTTON_LEFT:
            return s_ButtonTextList[0];
            break;

        case SDL_BUTTON_RIGHT:
            return s_ButtonTextList[1];
            break;

        case SDL_BUTTON_MIDDLE:
            return s_ButtonTextList[2];
            break;

        default:
            break;
        }
        return "INVALID";
    }
    static constexpr const char *s_ButtonTextList[] = {"LEFT", "RIGHT", "MIDDLE"};
};