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
        throw std::logic_error("Tag beginning expected");
    }

    position_ = tagBeginPosition + 1;
    
    std::string tagName = ReadTagName();
    thisNode.SetTagName(tagName);

    size_t nextTagBeginPosition = html_.find("<", position_);
    
    return thisNode;
}

std::string Parser::ReadTagName()
{
    size_t tagEndPos = html_.find(">", position_);

    std::string tagName = html_.substr(position_, tagEndPos - position_);

    position_ = tagEndPos;
    return tagName;
}
