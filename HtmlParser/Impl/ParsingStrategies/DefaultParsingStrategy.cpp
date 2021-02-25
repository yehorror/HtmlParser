#include "DefaultParsingStrategy.hpp"
#include "TagParser.hpp"
#include "Node.hpp"
#include "HtmlStream/HtmlStream.hpp"

#include <stdexcept>

using namespace HtmlParser::Impl;

namespace
{
}

DefaultParsingStrategy::DefaultParsingStrategy(Node& node, HtmlStream& stream)
    : AbstractParsingStrategy(node, stream)
{
}

void DefaultParsingStrategy::ParseNode()
{
    const std::string openTag = stream_.ReadTag();

    // parse first tag and then parse the rest of the node (text, child nodes, etc)
    ParseTag(openTag, node_);
    InnerParseNode();
}

void DefaultParsingStrategy::InnerParseNode()
{
    std::string nextTag;
    std::string text;
    bool nextTagIsClosing;
    do
    {
        text += stream_.ReadTextUntilTagBegins();
        nextTag = stream_.ReadTag();

        nextTagIsClosing = IsClosingTag(nextTag);
        if (!nextTagIsClosing)
        {
            Node childNode;

            ParseTag(nextTag, childNode);

            DefaultParsingStrategy childNodeParsingStrategy(childNode, stream_);
            childNodeParsingStrategy.InnerParseNode();

            node_.AppendChild(childNode);
        }
    }
    while (!nextTagIsClosing);

    node_.SetValue(text);

    const std::string closingTagName = ParseClosingTag(nextTag);

    if (closingTagName != node_.GetTagName())
    {
        throw std::logic_error("Unexpected closing tag name");
    }
}