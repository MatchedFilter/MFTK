#pragma once
#include <exception>

namespace MFTK
{
    class WidgetNotAddedToWindowException : public std::exception
    {
    public:
        const char *what()
        {
            return "Widget not added to window!";
        }
    };
} // namespace MFTK

