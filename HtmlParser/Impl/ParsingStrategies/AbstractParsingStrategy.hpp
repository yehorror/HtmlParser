#pragma once

namespace HtmlParser
{
    class Node;
    class Tag;

    namespace Impl
    {
        class HtmlStream;

        class AbstractParsingStrategy
        {
        public:
            AbstractParsingStrategy(Node& parentNode, HtmlStream& stream, const Tag& nodeTag)
                : parentNode_(parentNode)
                , stream_(stream)
                , nodeTagData_(nodeTag)
            {}

            virtual void ParseNode() = 0;
            virtual ~AbstractParsingStrategy()
            {}

        protected:
            Node& parentNode_;
            HtmlStream& stream_;
            const Tag& nodeTagData_;
        };
    }
}