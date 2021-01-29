#include <gtest/gtest.h>
#include "Impl/TagParsing/TagParser.hpp"
#include "Node.hpp"

using namespace HtmlParser::Impl;

TEST(TagParser, TestParsingOfATagName)
{
    const std::string TAG = "<head>";

    HtmlParser::Node tagNode;
    ParseTag(TAG, tagNode);

    EXPECT_EQ(tagNode.GetTagName(), "head");
}

TEST(TagParser, TestThrowIfTagHasUnexpectedBegin)
{
    const std::string TAG = "head>";

    HtmlParser::Node tagNode;

    EXPECT_THROW(ParseTag(TAG, tagNode), std::logic_error);
}

TEST(TagParser, TestParsingOfATagNameWithSpacesBetweenBeginAndName)
{
    const std::string TAG = "<  head>";

    HtmlParser::Node tagNode;
    ParseTag(TAG, tagNode);

    EXPECT_EQ(tagNode.GetTagName(), "head");
}

TEST(TagParser, TestParsingOfATagNameWithSpacesAfterName)
{
    const std::string TAG = "<head  >";

    HtmlParser::Node tagNode;
    ParseTag(TAG, tagNode);

    EXPECT_EQ(tagNode.GetTagName(), "head");
}

TEST(TagParser, TestThrowIfTagEndsWithSpace)
{
    const std::string TAG = "<head ";

    HtmlParser::Node tagNode;
    EXPECT_THROW(ParseTag(TAG, tagNode), std::logic_error);
}

TEST(TagParser, TestTagParsingWithAttributes)
{
    const std::string TAG = R"(<head attribute1="value" attribute2="value2">")";

    HtmlParser::Node tagNode;
    ParseTag(TAG, tagNode);

    EXPECT_EQ(tagNode.GetTagName(), "head");
    EXPECT_EQ(tagNode.GetAttribute("attribute1"), "value");
    EXPECT_EQ(tagNode.GetAttribute("attribute2"), "value2");
}