#pragma once
#include <exception>

namespace MFTK
{
    class UnableToCreateWindowException : public std::exception
    {
    public:
        const char *what()
        {
            return "Unable to Create Window";
        }
    };
} // namespace MFTK

