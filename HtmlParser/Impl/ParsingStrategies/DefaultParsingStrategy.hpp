#pragma once

#include "AbstractParsingStrategy.hpp"

namespace HtmlParser
{
    namespace Impl
    {
        class DefaultParsingStrategy : public AbstractParsingStrategy
        {
        public:
            DefaultParsingStrategy(Node& parentNode, HtmlStream& stream, const Tag& nodeTag);
            void ParseNode() override;
        };
    }
}