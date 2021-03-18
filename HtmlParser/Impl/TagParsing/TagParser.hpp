#pragma once

#include <string>

namespace HtmlParser
{
    class Tag;

    namespace Impl
    {
        void ParseTag(const std::string& tag, Tag& tagData);
        std::string ParseClosingTag(const std::string& tag);
        bool IsClosingTag(const std::string& tag);
    }
}