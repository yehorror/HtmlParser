#include "Utils.hpp"

size_t HtmlParser::Impl::Utils::FindClosestSymbol(const std::string& string, char firstSymbol, char secondSymbol, size_t offset)
{
    return 
        std::min(
            string.find(firstSymbol, offset),
            string.find(secondSymbol, offset)
        );
}

std::string HtmlParser::Impl::Utils::SubStringFromRange(const std::string& string, size_t begin, size_t end)
{
    return string.substr(begin, end - begin);
}