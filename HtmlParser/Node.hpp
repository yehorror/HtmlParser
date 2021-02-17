#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace HtmlParser
{
    class Node
    {
    public:
        void SetTagName(const std::string& tagName);
        const std::string& GetTagName() const;

        void SetAttribute(const std::string& attributeName, const std::string& attributeValue);
        const std::string& GetAttribute(const std::string& attributeName) const;

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
        std::unordered_map<std::string, std::string> attributes_;
        std::vector<Node> childNodes_;
        std::string tagName_;
        std::string value_;
    };
}
