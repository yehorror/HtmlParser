#include "Node.hpp"

using namespace HtmlParser;

const Tag& Node::GetTag() const
{
    return tagData_;
}

void Node::SetTag(const Tag& tagData)
{
    tagData_ = tagData;
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
        tagData_ == rhs.tagData_;
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
