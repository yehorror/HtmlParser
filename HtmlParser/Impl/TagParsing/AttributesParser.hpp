#pragma once

#include <string>

namespace HtmlParser
{
    class Tag;

    namespace Impl
    {
        void ParseAttributes(const std::string& attributesStr, Tag& tag);
    }
}
