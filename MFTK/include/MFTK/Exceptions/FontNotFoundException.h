#pragma once
#include <exception>
#include <string_view>
#include <string>

namespace MFTK
{
    class FontNotFoundException : public std::exception
    {
    public:
        FontNotFoundException(const char *fontPath) {
            m_ExceptionMsg = "Unable to find \"" ;
            m_ExceptionMsg += fontPath;
            m_ExceptionMsg += "\" font";

        }
        const char *what()
        {
            return m_ExceptionMsg.c_str();
        }

    private:
        std::string m_ExceptionMsg;
    };
} // namespace MFTK

