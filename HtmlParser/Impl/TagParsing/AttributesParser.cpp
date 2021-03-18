#include "AttributesParser.hpp"
#include "ParserConstants.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include <algorithm>

using namespace HtmlParser;

void Impl::ParseAttributes(const std::string& attributesStr, Tag& tag)
{
    size_t attributeOffset = 0;
    while (attributeOffset != std::string::npos)
    {
        size_t attributeNameEndPos = 
            Utils::FindClosestSymbol(
                attributesStr, 
                Impl::Constants::EQUALS_SIGN, 
                Impl::Constants::SPACE,
                attributeOffset
            );
        std::string attributeName = Utils::SubStringFromRange(attributesStr, attributeOffset, attributeNameEndPos);

        size_t valueStartPos = attributesStr.find(Impl::Constants::QUOTE, attributeNameEndPos) + 1;
        size_t valueEndPos = attributesStr.find(Impl::Constants::QUOTE, valueStartPos);

        std::string attributeValue = Utils::SubStringFromRange(attributesStr, valueStartPos, valueEndPos);

        tag.SetAttribute(attributeName, attributeValue);

        attributeOffset = attributesStr.find_first_not_of(Impl::Constants::SPACE, valueEndPos + 1);
    }
}
