#include "TagParser.hpp"
#include "Node.hpp"
#include "ParserConstants.hpp"
#include "AttributesParser.hpp"
#include <algorithm>

using namespace HtmlParser;

void Impl::ParseTag(const std::string& tag, Node& node)
{
    if (tag.at(0) != Impl::Constants::TAG_BEGIN)
    {
        throw std::logic_error("Expected tag begin");
    }

    const size_t TAG_NAME_BEGIN_OFFSET = 1;

    size_t nameOffset = tag.find_first_not_of(Impl::Constants::SPACE, TAG_NAME_BEGIN_OFFSET);
    size_t nameEndOffset =
        std::min(
            tag.find(Impl::Constants::TAG_END, nameOffset),
            tag.find(Impl::Constants::SPACE, nameOffset)
        );
    
    node.SetTagName(
        tag.substr(nameOffset, nameEndOffset - nameOffset)
    );

    if (tag.at(nameEndOffset) == Impl::Constants::SPACE)
    {
        size_t notSpaceCharOffset = 
            tag.find_first_not_of(Impl::Constants::SPACE, nameEndOffset);

        if (notSpaceCharOffset == std::string::npos)
        {
            throw std::logic_error("Expected end of a tag");
        }
        else if (tag.at(notSpaceCharOffset) != Impl::Constants::TAG_END)
        {
            size_t tagEndOffset = tag.find(Impl::Constants::TAG_END, notSpaceCharOffset);
            if (tagEndOffset == std::string::npos)
            {
                throw std::logic_error("Expected end of a tag");
            }

            const std::string attributesStr = tag.substr(notSpaceCharOffset, tagEndOffset - notSpaceCharOffset);
            ParseAttributes(attributesStr, node);
        }
    }
}
