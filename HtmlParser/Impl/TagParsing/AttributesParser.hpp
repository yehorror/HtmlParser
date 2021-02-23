#pragma once

#include <string>

namespace HtmlParser
{
    class Node;

    namespace Impl
    {
        void ParseAttributes(const std::string& attributesStr, Node& node);
    }
}
