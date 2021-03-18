#include <gtest/gtest.h>
#include "Tag.hpp"

using namespace HtmlParser;

TEST(TagTest, TestSetAndGetTagName)
{
    const std::string TAG_NAME = "test";

    Tag tag;
    tag.SetName(TAG_NAME);

    const std::string tagName = tag.GetName();

    EXPECT_EQ(TAG_NAME, tagName);
}

TEST(TagTest, TestAddingAngSettingOfAnAttributes)
{
    const std::string FIRST_ATTRIBUTE_NAME = "attribute1";
    const std::string FIRST_ATTRIBUTE_VALUE = "value1";

    const std::string SECOND_ATTRIBUTE_NAME = "attribute2";
    const std::string SECOND_ATTRIBUTE_VALUE = "value2";

    Tag tag;
    tag.SetAttribute(FIRST_ATTRIBUTE_NAME, FIRST_ATTRIBUTE_VALUE);
    tag.SetAttribute(SECOND_ATTRIBUTE_NAME, SECOND_ATTRIBUTE_VALUE);

    const std::string tagFirstAttributeValue = tag.GetAttribute(FIRST_ATTRIBUTE_NAME);
    const std::string tagSecondAttributeValue = tag.GetAttribute(SECOND_ATTRIBUTE_NAME);

    EXPECT_EQ(FIRST_ATTRIBUTE_VALUE, tagFirstAttributeValue);
    EXPECT_EQ(SECOND_ATTRIBUTE_VALUE, tagSecondAttributeValue);
}
