#pragma once
#include <string>
#include <string_view>

namespace MFTK
{
    class UtfConverter
    {
    public:
        static std::u32string ConvertFromUtf8ToUtf32(const std::string_view& utf8String);
        static std::string ConvertFromUtf32ToUtf8(const std::u32string_view& utf32String);
    };
} // namespace MFTK
