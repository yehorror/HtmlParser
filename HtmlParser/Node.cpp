#include "Node.hpp"

using namespace HtmlParser;

void Node::SetTagName(const std::string& tagName)
{
    tagName_ = tagName;
}

const std::string& Node::GetTagName() const
{
    return tagName_;
}

void Node::SetAttribute(const std::string& attributeName, const std::string& attributeValue)
{
    attributes_[attributeName] = attributeValue;
}

const std::string& Node::GetAttribute(const std::string& attributeName) const
{
    return attributes_.at(attributeName);
}

void Node::SetValue(const std::string& value)
{
    value_ = value;
}

const std::string& Node::GetValue() const
{
    return value_;
}

bool Node::operator == (const Node& rhs) const
{
    return
        value_ == rhs.value_ &&
        tagName_ == rhs.tagName_ &&
        attributes_ == rhs.attributes_;
}

bool Node::operator != (const Node& rhs) const
{
    return !(rhs == *this);
}

void Node::AppendChild(const Node& node)
{
    childNodes_.push_back(node);
}

Node& Node::GetChildNode(size_t index)
{
    return childNodes_.at(index);
}

void Node::RemoveChild(size_t index)
{
    childNodes_.erase(childNodes_.begin() + index);
}

bool Node::Empty() const
{
    return childNodes_.empty();
}
