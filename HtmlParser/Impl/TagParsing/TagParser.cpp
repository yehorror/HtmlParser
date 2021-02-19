#include "TagParser.hpp"
#include "Node.hpp"
#include "ParserConstants.hpp"
#include "AttributesParser.hpp"
#include "Utils.hpp"

#include <stdexcept>
#include <algorithm>

using namespace HtmlParser;

namespace
{
    const size_t TAG_NAME_BEGIN_OFFSET = 1;

    void CheckTagBeginCorrectness(const std::string& tag)
    {
        if (tag.at(0) != Impl::Constants::TAG_BEGIN)
        {
            throw std::logic_error("Expected tag begin");
        }
        size_t firstNotSpaceSymbol = tag.find_first_not_of(Impl::Constants::SPACE, TAG_NAME_BEGIN_OFFSET);
        if (tag.at(firstNotSpaceSymbol) == Impl::Constants::TAG_BEGIN)
        {
            throw std::logic_error("Unexpected second tag begin symbol");
        }
    }

    void CheckTagEndCorrectness(const std::string& tag)
    {
        if (tag.back() != Impl::Constants::TAG_END)
        {
            throw std::logic_error("Unexpected tag ending");
        }
    }

    size_t GetNameOffset(const std::string& tag, size_t offset)
    {
        return tag.find_first_not_of(Impl::Constants::SPACE, offset);
    }

    size_t GetNameEndOffset(const std::string& tag, size_t offset)
    {
        return 
            Impl::Utils::FindClosestSymbol(
                tag,
                Impl::Constants::SPACE,
                Impl::Constants::TAG_END,
                offset
            );
    }
}

void Impl::ParseTag(const std::string& tag, Node& node)
{
    CheckTagBeginCorrectness(tag);
    CheckTagEndCorrectness(tag);

    size_t nameBeginOffset = GetNameOffset(tag, TAG_NAME_BEGIN_OFFSET);
    size_t nameEndOffset = GetNameEndOffset(tag, nameBeginOffset);

    std::string tagName = Utils::SubStringFromRange(tag, nameBeginOffset, nameEndOffset);
    
    node.SetTagName(tagName);

    if (tag.at(nameEndOffset) == Impl::Constants::SPACE)
    {
        size_t notSpaceCharOffset = 
            tag.find_first_not_of(Impl::Constants::SPACE, nameEndOffset);

        Utils::CheckForNPos(notSpaceCharOffset, "Expected end of a tag");

        if (tag.at(notSpaceCharOffset) != Impl::Constants::TAG_END)
        {
            size_t tagEndOffset = tag.find(Impl::Constants::TAG_END, notSpaceCharOffset);

            const std::string attributesStr = Utils::SubStringFromRange(tag, notSpaceCharOffset, tagEndOffset);
            ParseAttributes(attributesStr, node);
        }
    }
}

std::string Impl::ParseClosingTag(const std::string& tag)
{
    CheckTagBeginCorrectness(tag);
    CheckTagEndCorrectness(tag);

    size_t tagSlashOffset = tag.find(Impl::Constants::FRONT_SLASH);

    Utils::CheckForNPos(tagSlashOffset, "Closing tag has no slash");

    size_t nameBeginOffset = GetNameOffset(tag, tagSlashOffset + 1);
    size_t nameEndOffset = GetNameEndOffset(tag, nameBeginOffset);

    std::string name = Utils::SubStringFromRange(tag, nameBeginOffset, nameEndOffset);

    return name;
}

bool Impl::IsClosingTag(const std::string& tag)
{
    return tag.find(Constants::FRONT_SLASH) != std::string::npos;
}