#include "Node.hpp"

using namespace HtmlParser;

void Node::SetTagName(const std::string& tagName)
{
    tagName_ = tagName;
}

std::string Node::GetTagName() const
{
    return tagName_;
}

void Node::SetAttribute(const std::string& attributeName, const std::string& attributeValue)
{
    attributes_[attributeName] = attributeValue;
}

std::string Node::GetAttribute(const std::string& attributeName) const
{
    return attributes_.at(attributeName);
}

void Node::SetValue(const std::string& value)
{
    value_ = value;
}

std::string Node::GetValue() const
{
    return value_;
}
