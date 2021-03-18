#pragma once

#include <string>
#include <unordered_map>

namespace HtmlParser
{
    class Tag
    {
    public:
        void SetName(const std::string& tagName);
        const std::string& GetName() const;

        void SetAttribute(const std::string& attributeName, const std::string& attributeValue);
        const std::string& GetAttribute(const std::string& attributeName) const;

    public:
        bool operator == (const Tag& rhs) const;
        bool operator != (const Tag& rhs) const;

    private:
        std::unordered_map<std::string, std::string> attributes_;
        std::string name_;
    };
}