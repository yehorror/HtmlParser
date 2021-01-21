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
        std::string GetTagName() const;

        void SetAttribute(const std::string& attributeName, const std::string& attributeValue);
        std::string GetAttribute(const std::string& attributeName) const;

        void SetValue(const std::string& value);
        std::string GetValue() const;

    private:
        std::unordered_map<std::string, std::string> attributes_;
        std::string tagName_;
        std::string value_;
    };
}