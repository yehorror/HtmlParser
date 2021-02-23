#include "HtmlStream.hpp"
#include "ParserConstants.hpp"
#include "Utils.hpp"

using namespace HtmlParser::Impl;

HtmlStream::HtmlStream(const std::string& html)
    :   html_(html)
    ,   position_(0)
{
}

std::string HtmlStream::ReadTag()
{
    const size_t tagBeginPosition = html_.find(Constants::TAG_BEGIN, position_);
    Utils::CheckForNPos(tagBeginPosition, "Tag beginning expected");

    position_ = html_.find(Constants::TAG_END, tagBeginPosition);
    Utils::CheckForNPos(position_, "Tag ending expected");

    ++position_;
    return Utils::SubStringFromRange(html_, tagBeginPosition, position_);
}

std::string HtmlStream::ReadTextUntilTagBegins()
{
    const size_t beginPosition = position_;

    position_ = html_.find(Constants::TAG_BEGIN, position_);
    Utils::CheckForNPos(position_, "Expected begin of a next tag");

    return Utils::SubStringFromRange(html_, beginPosition, position_);
}