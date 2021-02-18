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

    const size_t tagBeginPosition = html_.find(Constants::TAG_BEGIN, position_);
    Utils::CheckForNPos(tagBeginPosition, "Tag beginning expected");

    const size_t tagEndPosition = html_.find(Constants::TAG_END, tagBeginPosition) + 1;
    Utils::CheckForNPos(tagEndPosition, "Tag ending expected");

    const std::string tag = Utils::SubStringFromRange(html_, tagBeginPosition, tagEndPosition);

    ParseTag(tag, thisNode);

    const size_t nextTagBeginPosition = html_.find(Constants::TAG_BEGIN, tagEndPosition);
    Utils::CheckForNPos(nextTagBeginPosition, "Next tag begin expected");

    const size_t nextTagEndPosition = html_.find(Constants::TAG_END, nextTagBeginPosition) + 1;
    Utils::CheckForNPos(nextTagEndPosition, "Expected closing tag end");

    if (html_.at(nextTagBeginPosition + 1) != Constants::FRONT_SLASH)
    {
        position_ = nextTagBeginPosition;
        Node childNode = Parse();
        thisNode.AppendChild(childNode);
    }
    else
    {
        const std::string textBetweenTags = Utils::SubStringFromRange(html_, tagEndPosition, nextTagBeginPosition);
        thisNode.SetValue(textBetweenTags);

        const std::string closingTag = Utils::SubStringFromRange(html_, nextTagBeginPosition, nextTagEndPosition);
        const std::string closingTagName = ParseClosingTag(closingTag);

        if (closingTagName != thisNode.GetTagName())
        {
            throw std::logic_error("Unexpected closing tag name");
        }
    }

    return thisNode;
}