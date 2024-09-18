#include "MFTK/Common/Utils/UtfConverter.h"
#include <iostream>
#include <string>
#include <vector>

using namespace MFTK;

std::u32string UtfConverter::ConvertFromUtf8ToUtf32(const std::string_view& utf8String)
{
    std::u32string utf32String;
    auto it = utf8String.begin();
    auto end = utf8String.end();

    while (it != end) {
        char32_t codePoint = 0;
        unsigned char byte = static_cast<unsigned char>(*it);

        if ((byte & 0x80) == 0)
        {
            // 1-byte UTF-8 (ASCII)
            codePoint = byte;
            ++it;
        }
        else if ((byte & 0xE0) == 0xC0)
        {
            // 2-byte UTF-8
            if (std::distance(it, end) < 2) {
                throw std::runtime_error("Invalid UTF-8 sequence");
            }
            codePoint = (byte & 0x1F) << 6;
            codePoint |= (static_cast<unsigned char>(*(++it)) & 0x3F);
            ++it;
        }
        else if ((byte & 0xF0) == 0xE0)
        {
            // 3-byte UTF-8
            if (std::distance(it, end) < 3) {
                throw std::runtime_error("Invalid UTF-8 sequence");
            }
            codePoint = (byte & 0x0F) << 12;
            codePoint |= (static_cast<unsigned char>(*(++it)) & 0x3F) << 6;
            codePoint |= (static_cast<unsigned char>(*(++it)) & 0x3F);
            ++it;
        }
        else if ((byte & 0xF8) == 0xF0)
        {
            // 4-byte UTF-8
            if (std::distance(it, end) < 4)
            {
                throw std::runtime_error("Invalid UTF-8 sequence");
            }
            codePoint = (byte & 0x07) << 18;
            codePoint |= (static_cast<unsigned char>(*(++it)) & 0x3F) << 12;
            codePoint |= (static_cast<unsigned char>(*(++it)) & 0x3F) << 6;
            codePoint |= (static_cast<unsigned char>(*(++it)) & 0x3F);
            ++it;
        }
        else
        {
            throw std::runtime_error("Invalid UTF-8 sequence");
        }

        utf32String.push_back(codePoint);
    }

    return utf32String;
}


std::string UtfConverter::ConvertFromUtf32ToUtf8(const std::u32string_view& utf32String)
{
    std::string utf8_str;

    for (char32_t codePoint : utf32String)
    {
        if (codePoint <= 0x7F)
        {
            // 1-byte UTF-8
            utf8_str.push_back(static_cast<char>(codePoint));
        }
        else if (codePoint <= 0x7FF)
        {
            // 2-byte UTF-8
            utf8_str.push_back(static_cast<char>(0xC0 | (codePoint >> 6)));
            utf8_str.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
        }
        else if (codePoint <= 0xFFFF)
        {
            // 3-byte UTF-8
            utf8_str.push_back(static_cast<char>(0xE0 | (codePoint >> 12)));
            utf8_str.push_back(static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
            utf8_str.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
        }
        else if (codePoint <= 0x10FFFF)
        {
            // 4-byte UTF-8
            utf8_str.push_back(static_cast<char>(0xF0 | (codePoint >> 18)));
            utf8_str.push_back(static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F)));
            utf8_str.push_back(static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
            utf8_str.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
        }
        else
        {
            throw std::runtime_error("Invalid UTF-32 code point");
        }
    }

    return utf8_str;
}
