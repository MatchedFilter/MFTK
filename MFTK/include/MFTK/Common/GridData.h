#pragma once
#include <SDL_stdinc.h>

namespace MFTK
{
    struct GridData
    {
        Sint32 row = 0;
        Sint32 column = 0;
        Sint32 rowSpan = 1; 
        Sint32 columnSpan = 1; 
    };
} // namespace MFTK

