#pragma once

#include <cstddef>
#include "Node.hpp"
#include "HtmlStream/HtmlStream.hpp"

namespace HtmlParser
{
    namespace Impl
    {
        class Parser
        {
        public:
            explicit Parser(const std::string& html);

        public:
            Node Parse();

        private:
            void ParseNode(Node& node);

        private:
            HtmlStream stream_;
        };
    }
}
