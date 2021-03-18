#include "DefaultParsingStrategy.hpp"
#include "TagParser.hpp"
#include "Node.hpp"
#include "Tag.hpp"
#include "HtmlStream/HtmlStream.hpp"

#include <stdexcept>

using namespace HtmlParser::Impl;

DefaultParsingStrategy::DefaultParsingStrategy(Node& parentNode, HtmlStream& stream, const Tag& nodeTag)
    : AbstractParsingStrategy(parentNode, stream, nodeTag)
{
}

void DefaultParsingStrategy::ParseNode()
{
    std::string nextTag;
    std::string text;

    Node thisNode;
    thisNode.SetTag(nodeTagData_);

    bool nextTagIsClosing;
    do
    {
        text += stream_.ReadTextUntilTagBegins();
        nextTag = stream_.ReadTag();

        nextTagIsClosing = IsClosingTag(nextTag);
        if (!nextTagIsClosing)
        {
            Tag nextTagData;
            ParseTag(nextTag, nextTagData);

            Node childNode;
            childNode.SetTag(nextTagData);

            DefaultParsingStrategy childNodeParsingStrategy(thisNode, stream_, nextTagData);
            childNodeParsingStrategy.ParseNode();
        }
    }
    while (!nextTagIsClosing);

    thisNode.SetValue(text);

    const std::string closingTagName = ParseClosingTag(nextTag);

    if (closingTagName != nodeTagData_.GetName())
    {
        throw std::logic_error("Unexpected closing tag name");
    }
    parentNode_.AppendChild(thisNode);
}