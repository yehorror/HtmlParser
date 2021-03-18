#pragma once

#include "Tag.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace HtmlParser
{
    class Node
    {
    public:
        const Tag& GetTag() const;
        void SetTag(const Tag& tagData);

        void SetValue(const std::string& value);
        const std::string& GetValue() const;

        void AppendChild(const Node& node);
        Node& GetChildNode(size_t index);
        void RemoveChild(size_t index);

        bool Empty() const;

    public:
        bool operator == (const Node& rhs) const;
        bool operator != (const Node& rhs) const;

    private:
        Tag tagData_;
        std::vector<Node> childNodes_;
        std::string value_;
    };
}
