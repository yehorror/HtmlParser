#include <gtest/gtest.h>
#include "Impl/TagParsing/AttributesParser.hpp"
#include "Tag.hpp"

using namespace HtmlParser;

TEST(AttributeParser, TestParsingOfAnAttribute)
{
    const std::string ATTRIBUTE = R"(attribute="value")";

    Tag tag;
    Impl::ParseAttributes(ATTRIBUTE, tag);

    EXPECT_EQ(tag.GetAttribute("attribute"), "value");
}

TEST(AttributeParser, TestParsingOfMultipleAttributes)
{
    const std::string ATTRIBUTE = R"(attribute1="value1" attribute2="value2")";

    Tag tag;
    Impl::ParseAttributes(ATTRIBUTE, tag);

    EXPECT_EQ(tag.GetAttribute("attribute1"), "value1");
    EXPECT_EQ(tag.GetAttribute("attribute2"), "value2");
}

TEST(AttributeParser, TestParsingOfMultipleAttributesWhenSpaceBetweenNameValueAndEqualsSign)
{
    const std::string ATTRIBUTE = R"(attribute1 = "value1" attribute2 = "value2")";

    Tag tag;
    Impl::ParseAttributes(ATTRIBUTE, tag);

    EXPECT_EQ(tag.GetAttribute("attribute1"), "value1");
    EXPECT_EQ(tag.GetAttribute("attribute2"), "value2");
}

