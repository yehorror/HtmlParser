#pragma once

#include <string>

namespace HtmlParser
{
    namespace Impl
    {
        namespace Utils
        {
            size_t FindClosestSymbol(const std::string& string, char firstSymbol, char secondSymbol, size_t offset);
            std::string SubStringFromRange(const std::string& string, size_t begin, size_t end);
        }
    }
}