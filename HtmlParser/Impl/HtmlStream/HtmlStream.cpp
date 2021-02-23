#include "HtmlStream.hpp"

using namespace HtmlParser::Impl;

HtmlStream::HtmlStream(const std::string& html)
    :   html_(html)
    ,   position_(0)
{
}

std::string HtmlStream::ReadTag()
{

}

std::string HtmlStream::ReadTextUntilTagBegins()
{

}