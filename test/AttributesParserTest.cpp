#include <gtest/gtest.h>
#include "TagParser.hpp"
#include "Node.hpp"

using namespace HtmlParser;

TEST(AttributeParser, TestParsingOfAnAttribute)
{
    const std::string ATTRIBUTE = R"(attribute="value")";

    Node node;
    Impl::ParseAttributes(ATTRIBUTE, node);

    EXPECT_EQ(node.GetAttribute("attribute"), "value");
}

TEST(AttributeParser, TestParsingOfMultipleAttributes)
{
    const std::string ATTRIBUTE = R"(attribute1="value1" attribute2="value2")";

    Node node;
    Impl::ParseAttributes(ATTRIBUTE, node);

    EXPECT_EQ(node.GetAttribute("attribute1"), "value1");
    EXPECT_EQ(node.GetAttribute("attribute2"), "value2");
}

TEST(AttributeParser, TestParsingOfMultipleAttributesWhenSpaceBetweenNameValueAndEqualsSign)
{
    const std::string ATTRIBUTE = R"(attribute1 = "value1" attribute2 = "value2")";

    Node node;
    Impl::ParseAttributes(ATTRIBUTE, node);

    EXPECT_EQ(node.GetAttribute("attribute1"), "value1");
    EXPECT_EQ(node.GetAttribute("attribute2"), "value2");
}

