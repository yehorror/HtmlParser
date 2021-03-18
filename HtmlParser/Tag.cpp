#include "Tag.hpp"

using namespace HtmlParser;

void Tag::SetName(const std::string& tagName)
{
    name_ = tagName;
}

const std::string& Tag::GetName() const
{
    return name_;
}

void Tag::SetAttribute(const std::string& attributeName, const std::string& attributeValue)
{
    attributes_[attributeName] = attributeValue;
}

const std::string& Tag::GetAttribute(const std::string& attributeName) const
{
    return attributes_.at(attributeName);
}

bool Tag::operator == (const Tag& rhs) const
{
    return name_ == rhs.name_ && attributes_ == rhs.attributes_;
}

bool Tag::operator != (const Tag& rhs) const
{
    return !(*this == rhs);
}