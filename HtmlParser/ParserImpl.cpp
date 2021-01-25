#include "ParserImpl.hpp"

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

    size_t tagBeginPosition = html_.find("<", position_);

    if (tagBeginPosition == std::string::npos)
    {
        throw std::logic_error("Tried to start parsig not from a tag");
    }

    position_ = tagBeginPosition + 1;
    
    std::string tagName = ReadTagName();
    thisNode.SetTagName(tagName);

    return thisNode;
}

std::string Parser::ReadTagName()
{
    size_t tagEndPos = html_.find(">", position_);

    std::string tagName = html_.substr(position_, tagEndPos - position_);

    position_ = tagEndPos;
    return tagName;
}
