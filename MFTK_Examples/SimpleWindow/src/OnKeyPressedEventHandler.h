#pragma once
#include "MFTK/Tk.h"
#include "MFTK/Widget/WidgetEventHandler/IWidgetKeyPressedEventHandler.h"
#include <iostream>
#include <string>
#include <wchar.h>

class OnKeyPressedEventHandler : public MFTK::IWidgetKeyPressedEventHandler
{
public:
    OnKeyPressedEventHandler() = default;
    ~OnKeyPressedEventHandler() = default;
    virtual void OnKeyPressed(MFTK::Widget *widget, const SDL_Event *event) override
    {
        if (widget->IsFocused())
        {
            if (event->key.keysym.sym == SDLK_RETURN)
            {
                std::cout << "<RETURN>";
                std::cout.flush();
            }
            else if (event->key.keysym.sym == SDLK_LSHIFT)
            {
                std::cout << "<LSHIFT>";
                std::cout.flush();
            }
            else
            {
                if (event->key.keysym.sym == 305) // Turkish char
                {
                    const char lowerI[] = {(char)0xC4, (char)0xB1, (char) 0x00};
                    printf("%s", lowerI);
                    fflush(stdout);
                }
                char32_t key = event->key.keysym.sym;
                const char *str = (const char *) &key;
                std::cout <<" [" << str;
                std::cout << ", "<< event->key.keysym.sym << "] ";
                std::cout.flush();
            }
        }
    }
};