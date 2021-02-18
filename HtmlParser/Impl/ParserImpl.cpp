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

    const size_t closingTagBeginPosition = html_.find(Constants::TAG_BEGIN, tagEndPosition);
    Utils::CheckForNPos(closingTagBeginPosition, "Closing tag begin expected");

    const std::string textBetweenTags = Utils::SubStringFromRange(html_, tagEndPosition, closingTagBeginPosition);

    thisNode.SetValue(textBetweenTags);

    return thisNode;
}