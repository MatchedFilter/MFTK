#include "MFTK/ResourceManager/ResourceManager.h"
#include <unordered_map>
#include "MFTK/Exceptions/FontNotFoundException.h"
#include <SDL_ttf.h>

using namespace MFTK;

SDL_Cursor *s_SdlCursors[SDL_NUM_SYSTEM_CURSORS] = { 0 };
static std::unordered_map<std::string_view, std::string_view> s_FontsPathMap;

static void InitializeCursors()
{
    s_SdlCursors[SDL_SYSTEM_CURSOR_ARROW]       = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    s_SdlCursors[SDL_SYSTEM_CURSOR_IBEAM]       = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    s_SdlCursors[SDL_SYSTEM_CURSOR_WAIT]        = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
    s_SdlCursors[SDL_SYSTEM_CURSOR_CROSSHAIR]   = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    s_SdlCursors[SDL_SYSTEM_CURSOR_WAITARROW]   = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZENWSE]    = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZENESW]    = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZEWE]      = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZENS]      = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZEALL]     = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    s_SdlCursors[SDL_SYSTEM_CURSOR_NO]          = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    s_SdlCursors[SDL_SYSTEM_CURSOR_HAND]        = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

static void InitializeFonts()
{
    TTF_Init();
    s_FontsPathMap["JetBrains Mono"] = "resources/JetBrains_Mono/static/JetBrainsMono-Medium.ttf";
}

void ResourceManager::Initialize()
{
    InitializeCursors();
    InitializeFonts();
}

void ResourceManager::ChangeCursor(SDL_SystemCursor sdlCursor)
{
    SDL_SetCursor(s_SdlCursors[sdlCursor]);
}


TTF_Font* ResourceManager::CreateFont(FontData fontData)
{
    TTF_Font *font = nullptr;
    if (s_FontsPathMap.find(fontData.font) != s_FontsPathMap.end())
    {
        std::string_view fontPath = s_FontsPathMap.at(fontData.font);
        font = TTF_OpenFont(fontPath.data(), fontData.size);
    }
    else
    {
        font = TTF_OpenFont(fontData.font.data(), fontData.size);
    }

    if (font == nullptr)
    {
        throw FontNotFoundException(fontData.font.data());
    }
    return font;
}
