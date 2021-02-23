#pragma once

#include <string>

namespace HtmlParser
{
    namespace Impl
    {
        class HtmlStream
        {
        public:
            explicit HtmlStream(const std::string& string);

            std::string ReadTag();
            std::string ReadTextUntilTagBegins();

        private:
            std::string html_;
            size_t position_;
        };
    }
}