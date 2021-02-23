#pragma once

#include <string>

namespace HtmlParser
{
    class Node;

    namespace Impl
    {
        void ParseTag(const std::string& tag, Node& node);
        std::string ParseClosingTag(const std::string& tag);
        bool IsClosingTag(const std::string& tag);
    }
}