#include "ParserImpl.hpp"
#include "ParserConstants.hpp"
#include "TagParsing/TagParser.hpp"
#include "Utils.hpp"
#include "ParsingStrategies/DefaultParsingStrategy.hpp"

using HtmlParser::Node;
using namespace HtmlParser::Impl;

Parser::Parser(const std::string& html)
    : stream_(html)
{
}

Node Parser::Parse()
{
    Node rootNode;

    const std::string firstTag = stream_.ReadTag();

    Tag firstTagData;
    ParseTag(firstTag, firstTagData);

    DefaultParsingStrategy parsingStrategy(rootNode, stream_, firstTagData);
    parsingStrategy.ParseNode();

    return rootNode;
}
