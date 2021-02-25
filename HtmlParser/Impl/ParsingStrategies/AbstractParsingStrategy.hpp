#pragma once

namespace HtmlParser
{
    class Node;

    namespace Impl
    {
        class HtmlStream;

        class AbstractParsingStrategy
        {
        public:
            AbstractParsingStrategy(Node& node, HtmlStream& stream)
                : node_(node)
                , stream_(stream)
            {}

            virtual void ParseNode() = 0;
            virtual ~AbstractParsingStrategy()
            {}

        protected:
            Node& node_;
            HtmlStream& stream_;
        };
    }
}