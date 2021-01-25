#pragma once

#include <cstddef>
#include "Node.hpp"

namespace HtmlParser
{
    namespace Impl
    {
        class Parser
        {
        public:
            Parser(const std::string& html);

        public:
            Node Parse();

        private:
            std::string ReadTagName();

        private:
            std::string html_;
            size_t position_;
        };
    }
}
