#pragma once

#include <string>

namespace HtmlParser
{
    class Node;

    namespace Impl
    {
        void ParseTag(const std::string& tag, Node& node);
        void ParseAttributes(const std::string& attributesStr, Node& node);
    }
}