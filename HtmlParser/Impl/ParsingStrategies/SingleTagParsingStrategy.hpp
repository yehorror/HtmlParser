#pragma once

#include "AbstractParsingStrategy.hpp"

namespace HtmlParser
{
    namespace Impl
    {
        class SingleTagParsingStrategy : public AbstractParsingStrategy
        {
        public:
            SingleTagParsingStrategy(Node& parentNode, HtmlStream& stream, const Tag& nodeTag);
            void ParseNode() override;
        };
    }
}