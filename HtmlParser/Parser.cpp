#include "Parser.hpp"
#include "ParserImpl.hpp"

#include <stdexcept>

HtmlParser::Node HtmlParser::Parse(const std::string& html)
{
    if (html.empty())
    {
        throw std::logic_error("Empty HTML input");
    }

    Impl::Parser parserImpl(html);
    
    Node parsedNode = parserImpl.Parse();

    return parsedNode;
}
