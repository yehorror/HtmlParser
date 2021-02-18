#include "Parser.hpp"
#include "Impl/ParserImpl.hpp"

#include <stdexcept>

HtmlParser::Node HtmlParser::Parse(const std::string& html)
{
    if (html.empty())
    {
        throw std::logic_error("Empty HTML input");
    }

    return Impl::Parser(html).Parse();
}
