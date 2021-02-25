#include "ParserImpl.hpp"
#include "ParserConstants.hpp"
#include "TagParsing/TagParser.hpp"
#include "Utils.hpp"
#include "ParsingStrategies/DefaultParsingStrategy.hpp"

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

    DefaultParsingStrategy parsingStrategy(thisNode, stream_);
    parsingStrategy.ParseNode();

    return thisNode;
}
