#include "TagParser.hpp"
#include "Node.hpp"
#include "ParserConstants.hpp"
#include "AttributesParser.hpp"

#include <stdexcept>
#include <algorithm>

using namespace HtmlParser;

namespace
{
    const size_t TAG_NAME_BEGIN_OFFSET = 1;

    void CheckIfTagHasNoBegin(const std::string& tag)
    {
        if (tag.at(0) != Impl::Constants::TAG_BEGIN)
        {
            throw std::logic_error("Expected tag begin");
        }
    }

    size_t GetNameOffset(const std::string& tag, size_t offset)
    {
        return tag.find_first_not_of(Impl::Constants::SPACE, offset);
    }

    size_t GetNameEndOffset(const std::string& tag, size_t offset)
    {
        return 
            std::min(
                tag.find(Impl::Constants::TAG_END, offset),
                tag.find(Impl::Constants::SPACE, offset)
            );
    }
}

void Impl::ParseTag(const std::string& tag, Node& node)
{
    CheckIfTagHasNoBegin(tag);

    size_t nameBeginOffset = GetNameOffset(tag, TAG_NAME_BEGIN_OFFSET);
    size_t nameEndOffset = GetNameEndOffset(tag, nameBeginOffset);

    std::string tagName = tag.substr(nameBeginOffset, nameEndOffset - nameBeginOffset);
    
    node.SetTagName(tagName);

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
    CheckIfTagHasNoBegin(tag);

    size_t tagSlashOffset = tag.find(Impl::Constants::FRONT_SLASH);

    if (tagSlashOffset == std::string::npos)
    {
        throw std::logic_error("Closing tag has no slash");
    }

    size_t nameBeginOffset = GetNameOffset(tag, tagSlashOffset + 1);
    size_t nameEndOffset = GetNameEndOffset(tag, nameBeginOffset);

    std::string name = tag.substr(nameBeginOffset, nameEndOffset - nameBeginOffset);

    if (nameEndOffset == std::string::npos)
    {
        throw std::logic_error("Expected closing tag ending");
    }

    return name;
}
