#include <gtest/gtest.h>
#include "TagParser.hpp"
#include "Node.hpp"

using namespace HtmlParser::Impl;

TEST(TagParser, TestParsingOfTagName)
{
    const std::string TAG = "<head>";

    HtmlParser::Node tagNode;
    ParseTag(TAG, tagNode);

    EXPECT_EQ(tagNode.GetTagName(), "head");
}

TEST(TagParser, TestThrowIfTagHasUnexpectedBegin)
{
    const std::string TAG = "head";

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
