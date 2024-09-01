#pragma once
#include <exception>

namespace MFTK
{
    class NullWindowException : public std::exception
    {
    public:
        const char *what()
        {
            return "Window is not set, Null Window!";
        }
    };
} // namespace MFTK

