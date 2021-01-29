#include "AttributesParser.hpp"
#include "ParserConstants.hpp"
#include "Node.hpp"

#include <algorithm>

using namespace HtmlParser;

void Impl::ParseAttributes(const std::string& attributesStr, Node& node)
{
    size_t attributeOffset = 0;
    while (attributeOffset != std::string::npos)
    {
        size_t attributeNameEndPos = 
            std::min(
                attributesStr.find(Impl::Constants::EQUALS_SIGN, attributeOffset),
                attributesStr.find(Impl::Constants::SPACE, attributeOffset)
            );
        std::string attributeName = attributesStr.substr(attributeOffset, attributeNameEndPos - attributeOffset);

        size_t valueStartPos = attributesStr.find(Impl::Constants::QUOTE, attributeNameEndPos) + 1;
        size_t valueEndPos = attributesStr.find(Impl::Constants::QUOTE, valueStartPos);

        std::string attributeValue = attributesStr.substr(valueStartPos, valueEndPos - valueStartPos);

        node.SetAttribute(attributeName, attributeValue);

        attributeOffset = attributesStr.find_first_not_of(Impl::Constants::SPACE, valueEndPos + 1);
    }
}
