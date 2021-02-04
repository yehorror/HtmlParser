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

TEST(TagParser, TestClosingTagParsing)
{
    const std::string TAG = "</head>";
    const std::string TAG_NAME = "head";
    std::string parsedTagName = ParseClosingTag(TAG);

    EXPECT_EQ(TAG_NAME, parsedTagName);
}

TEST(TagParser, TestParsingOfATagWithSpaceBeforeName)
{
    const std::string TAG = "</ head>";
    const std::string TAG_NAME = "head";
    std::string parsedTagName = ParseClosingTag(TAG);

    EXPECT_EQ(TAG_NAME, parsedTagName);
}

TEST(TagParser, TestParsingOfATagWithSpacesBetweenBeginSlashAndName)
{
    const std::string TAG = "< / head>";
    const std::string TAG_NAME = "head";
    std::string parsedTagName = ParseClosingTag(TAG);

    EXPECT_EQ(TAG_NAME, parsedTagName);
}

TEST(TagParser, TestParsingOfATagSpacesBetweenNameAndEnding)
{
    const std::string TAG = "< / head >";
    const std::string TAG_NAME = "head";
    std::string parsedTagName = ParseClosingTag(TAG);

    EXPECT_EQ(TAG_NAME, parsedTagName);
}

TEST(TagParser, TestThrowIfTagHasUnexpectedBeginInClosingTag)
{
    const std::string TAG = "/head>";

    EXPECT_THROW(ParseClosingTag(TAG), std::logic_error);
}

TEST(TagParser, TestThrowIfClosingTagHasNoSlash)
{
    const std::string TAG = "<head>";

    EXPECT_THROW(ParseClosingTag(TAG), std::logic_error);
}
