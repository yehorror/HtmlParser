#include "ParserImpl.hpp"
#include "ParserConstants.hpp"
#include "TagParsing/TagParser.hpp"
#include "Utils.hpp"

#include <stdexcept>

using HtmlParser::Node;
using namespace HtmlParser::Impl;

Parser::Parser(const std::string& html)
    : html_(html)
    , position_(0)
{
}

Node Parser::Parse()
{
    Node thisNode;

    const std::string openTag = ReadTag();

    // parse first tag and then parse the rest of the node (text, child nodes, etc)
    ParseTag(openTag, thisNode);
    ParseNode(thisNode);

    return thisNode;
}

std::string Parser::ReadTag()
{
    const size_t tagBeginPosition = html_.find(Constants::TAG_BEGIN, position_);
    Utils::CheckForNPos(tagBeginPosition, "Tag beginning expected");

    position_ = html_.find(Constants::TAG_END, tagBeginPosition);
    Utils::CheckForNPos(position_, "Tag ending expected");

    ++position_;
    return Utils::SubStringFromRange(html_, tagBeginPosition, position_);
}

std::string Parser::ReadTextUntilTagBegins()
{
    const size_t beginPosition = position_;

    position_ = html_.find(Constants::TAG_BEGIN, position_);
    Utils::CheckForNPos(position_, "Expected begin of a next tag");

    return Utils::SubStringFromRange(html_, beginPosition, position_);
}

void Parser::ParseNode(Node& node)
{
    std::string nextTag;
    std::string text;
    bool nextTagIsClosing;
    do
    {
        text += ReadTextUntilTagBegins();
        nextTag = ReadTag();

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