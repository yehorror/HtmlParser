#pragma once

#include <string>

namespace HtmlParser
{
    class Node;

    namespace Impl
    {
        void ParseTag(const std::string& tag, Node& node);
    }
}