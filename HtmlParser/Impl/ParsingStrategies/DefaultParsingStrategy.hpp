#pragma once

#include "AbstractParsingStrategy.hpp"

namespace HtmlParser
{
    namespace Impl
    {
        class DefaultParsingStrategy : public AbstractParsingStrategy
        {
        public:
            DefaultParsingStrategy(Node& node, HtmlStream& stream);
            void ParseNode() override;
        private:
            void InnerParseNode();
        };
    }
}