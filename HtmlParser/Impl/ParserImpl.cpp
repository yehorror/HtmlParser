#include "ParserImpl.hpp"
#include "ParserConstants.hpp"
#include "TagParsing/TagParser.hpp"
#include "Utils.hpp"

#include <stdexcept>

using HtmlParser::Node;
using namespace HtmlParser::Impl;

Parser::Parser(const std::string& html)
    : stream_(html)
{
}

Node Parser::Parse()
{
    Node thisNode;

    const std::string openTag = stream_.ReadTag();

    // parse first tag and then parse the rest of the node (text, child nodes, etc)
    ParseTag(openTag, thisNode);
    ParseNode(thisNode);

    return thisNode;
}

void Parser::ParseNode(Node& node)
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
            ParseNode(childNode);

            node.AppendChild(childNode);
        }
    }
    while (!nextTagIsClosing);

    node.SetValue(text);

    const std::string closingTagName = ParseClosingTag(nextTag);

    if (closingTagName != node.GetTagName())
    {
        throw std::logic_error("Unexpected closing tag name");
    }
}