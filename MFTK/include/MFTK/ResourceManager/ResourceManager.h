#pragma once
#include <SDL.h>
#include "FontData.h"
#include <SDL_ttf.h>

namespace MFTK
{
    class ResourceManager
    {
    public:
        static void ChangeCursor(SDL_SystemCursor sdlCursor);
        static TTF_Font* CreateFont(FontData fontData);


    private:
        static void Initialize();
        friend class Tk;
    };
} // namespace MFTK
