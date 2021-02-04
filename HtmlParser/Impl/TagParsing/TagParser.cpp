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

        if (tag.at(notSpaceCharOffset) != Impl::Constants::TAG_END)
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

std::string Impl::ParseClosingTag(const std::string& tag)
{
    if (tag.at(0) != Impl::Constants::TAG_BEGIN)
    {
        throw std::logic_error("Expected tag begin");
    }

    size_t tagSlashOffset = tag.find(Impl::Constants::FRONT_SLASH);
    if (tagSlashOffset == std::string::npos)
    {
        throw std::logic_error("Closing tag has no slash");
    }
    size_t tagNameBeginOffset = tag.find_first_not_of(Impl::Constants::SPACE, tagSlashOffset + 1);

    const size_t endNameOffset = 
        std::min(
            tag.find(Impl::Constants::TAG_END, tagNameBeginOffset),
            tag.find(Impl::Constants::SPACE, tagNameBeginOffset)
        );

    if (endNameOffset == std::string::npos)
    {
        throw std::logic_error("Expected closing tag ending");
    }

    return tag.substr(tagNameBeginOffset, endNameOffset - tagNameBeginOffset);
}
