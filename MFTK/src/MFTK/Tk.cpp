#include "MFTK/Tk.h"
#include "MFTK/Exceptions/UnableToCreateWindowException.h"
#include "MFTK/ResourceManager/ResourceManager.h"
#include <map>
#include <atomic>


using namespace MFTK;

Uint32 s_WidgetIDCounter = 0;
Uint32 Tk::s_Fps = 0;
std::map<Uint32, Window*> s_WindowMap;
static std::atomic_bool s_ApplicationRunning = true;

void Tk::HandleMainEvents(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        s_ApplicationRunning.store(false);
        break;

    case SDL_WINDOWEVENT:
        if (event->window.event == SDL_WINDOWEVENT_CLOSE)
        {
            if (s_WindowMap.find(event->window.windowID) != s_WindowMap.end())
            {
                Tk::DestroyWindow(s_WindowMap[event->window.windowID]);
            }
        }
        break;
    
    default:
        break;
    }
}

void Tk::Initialize(Uint32 fps)
{
    SDL_Init(SDL_INIT_VIDEO);
    s_Fps = fps;
    ResourceManager::Initialize();

}

void Tk::AddWindow(Window *window)
{
    SDL_Window *sdlWindow = SDL_CreateWindow(window->m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->m_Width, window->m_Height, SDL_WINDOW_SHOWN);
    if (sdlWindow == nullptr)
    {
        throw UnableToCreateWindowException();
    }
    Uint32 windowID = SDL_GetWindowID(sdlWindow);
    window->m_Window = sdlWindow;
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window->m_Window, -1, 0);
    if (sdlRenderer == nullptr)
    {
        throw UnableToCreateWindowException();
    }
    window->m_Renderer = sdlRenderer;
    window->m_ID = windowID;
    s_WindowMap[windowID] = window;
}


void Tk::DestroyApplication()
{
    s_ApplicationRunning.store(false);
}

void Tk::DestroyWindow(Window *window)
{
    s_WindowMap.erase(window->m_ID);
    window->Destroy();
}

void Tk::MainLoop()
{
    Uint64 frameStart;
    int32_t frameTime;
    int32_t frameDelay = 0;
    if (s_Fps != 0)
    {
        frameDelay = 1000 / s_Fps;
    }
    while (s_ApplicationRunning.load())
    {
        SDL_Event sdlEvent;
        frameStart = SDL_GetTicks64();
        while (SDL_PollEvent(&sdlEvent))
        {
            HandleMainEvents(&sdlEvent);
            for (auto &window : s_WindowMap)
            {
                window.second->HandleEvents(&sdlEvent);
            }
        }
        if (s_ApplicationRunning.load())
        {
            for (auto &window : s_WindowMap)
            {
                window.second->Render();
            }
            frameTime = static_cast<int32_t>(SDL_GetTicks64() - frameStart);
            if (frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }
}

Uint32 Tk::GenerateWidgetID()
{
    s_WidgetIDCounter++;
    return s_WidgetIDCounter;
}
