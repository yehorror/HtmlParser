#include <gtest/gtest.h>
#include "Node.hpp"

using namespace HtmlParser;

TEST(NodeTest, TestSetAndGetTagName)
{
    const std::string TAG_NAME = "test";

    Node node;
    node.SetTagName(TAG_NAME);

    const std::string nodeTagName = node.GetTagName();

    EXPECT_EQ(TAG_NAME, nodeTagName);
}

TEST(NodeTest, TestAddingAngSettingOfAnAttributes)
{
    const std::string FIRST_ATTRIBUTE_NAME = "attribute1";
    const std::string FIRST_ATTRIBUTE_VALUE = "value1";

    const std::string SECOND_ATTRIBUTE_NAME = "attribute2";
    const std::string SECOND_ATTRIBUTE_VALUE = "value2";

    Node node;
    node.SetAttribute(FIRST_ATTRIBUTE_NAME, FIRST_ATTRIBUTE_VALUE);
    node.SetAttribute(SECOND_ATTRIBUTE_NAME, SECOND_ATTRIBUTE_VALUE);

    const std::string nodeFirstAttributeValue = node.GetAttribute(FIRST_ATTRIBUTE_NAME);
    const std::string nodeSecondAttributeValue = node.GetAttribute(SECOND_ATTRIBUTE_NAME);

    EXPECT_EQ(FIRST_ATTRIBUTE_VALUE, nodeFirstAttributeValue);
    EXPECT_EQ(SECOND_ATTRIBUTE_VALUE, nodeSecondAttributeValue);
}

TEST(NodeTest, TestSetAndGetValue)
{
    const std::string VALUE = "value";

    Node node;
    node.SetValue(VALUE);

    const std::string nodeValue = node.GetValue();

    EXPECT_EQ(VALUE, nodeValue);
}
