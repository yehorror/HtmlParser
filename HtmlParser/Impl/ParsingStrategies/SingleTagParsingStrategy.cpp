#include "SingleTagParsingStrategy.hpp"

using namespace HtmlParser::Impl;

SingleTagParsingStrategy::SingleTagParsingStrategy(Node& parentNode, HtmlStream& stream, const Tag& nodeTag)
    :   AbstractParsingStrategy(parentNode, stream, nodeTag)
{
}

void SingleTagParsingStrategy::ParseNode()
{
}