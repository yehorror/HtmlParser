#include <gtest/gtest.h>
#include "Impl/TagParsing/TagParser.hpp"
#include "Tag.hpp"

using namespace HtmlParser;
using namespace HtmlParser::Impl;

TEST(TagParser, TestParsingOfATagName)
{
    const std::string TAG = "<head>";

    Tag tag;
    ParseTag(TAG, tag);

    EXPECT_EQ(tag.GetName(), "head");
}

TEST(TagParser, TestThrowIfTagHasUnexpectedBegin)
{
    const std::string TAG = "head>";

    Tag tag;

    EXPECT_THROW(ParseTag(TAG, tag), std::logic_error);
}

TEST(TagParser, TestParsingOfATagNameWithSpacesBetweenBeginAndName)
{
    const std::string TAG = "<  head>";

    Tag tag;
    ParseTag(TAG, tag);

    EXPECT_EQ(tag.GetName(), "head");
}

TEST(TagParser, TestParsingOfATagNameWithSpacesAfterName)
{
    const std::string TAG = "<head  >";

    Tag tag;
    ParseTag(TAG, tag);

    EXPECT_EQ(tag.GetName(), "head");
}

TEST(TagParser, TestThrowIfTagEndsWithSpace)
{
    const std::string TAG = "<head ";

    Tag tag;
    EXPECT_THROW(ParseTag(TAG, tag), std::logic_error);
}

TEST(TagParser, TestTagParsingWithAttributes)
{
    const std::string TAG = R"(<head attribute1="value" attribute2="value2">)";

    Tag tag;
    ParseTag(TAG, tag);

    EXPECT_EQ(tag.GetName(), "head");
    EXPECT_EQ(tag.GetAttribute("attribute1"), "value");
    EXPECT_EQ(tag.GetAttribute("attribute2"), "value2");
}

TEST(TagParser, TestThrowIfTagHasTwoLessThanSigns)
{
    const std::string TAG = "<<head>";
    Tag tag;

    EXPECT_THROW(ParseTag(TAG, tag), std::logic_error);
}

TEST(TagParser, TestThrowIfTagEndsWithNoTagEndSymbol)
{
    const std::string TAG = "<head> ";  // tag ends with space
    Tag tag;

    EXPECT_THROW(ParseTag(TAG, tag), std::logic_error);
}

TEST(TagParser, TestParsingOfTagWithSlashInAttributeValue)
{
    const std::string TAG = "<script type=\"text/javascript\">";
    Tag tag;
    ParseTag(TAG, tag);

    EXPECT_EQ(tag.GetAttribute("type"), "text/javascript");
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

TEST(TagParser, TestThrowIfClosingTagHasNoTagEnd)
{
    const std::string TAG = "</head";

    EXPECT_THROW(ParseClosingTag(TAG), std::logic_error);
}

TEST(TagParser, TestThrowIfTagHasCharactersBetweenTagBeginAndSlash)
{
    const std::string TAG = "<whatever/tag>";

    EXPECT_THROW(ParseClosingTag(TAG), std::logic_error);
}

TEST(TagParser, TestCheckingIfTagIsClosing)
{
    const std::string TAG = "</head>";

    EXPECT_TRUE(IsClosingTag(TAG));
}

TEST(TagParser, TestCheckingIfTagIsNotClosing)
{
    const std::string TAG = "<head>";

    EXPECT_FALSE(IsClosingTag(TAG));
}

TEST(TagParser, TestClosingTagCheckThrowIfItHasNoBegin)
{
    const std::string TAG = "/head>";

    EXPECT_THROW(IsClosingTag(TAG), std::logic_error);
}

TEST(TagParser, TestClosingTagCheckThrowIfItHasNoEnd)
{
    const std::string TAG = "</head";

    EXPECT_THROW(IsClosingTag(TAG), std::logic_error);
}

TEST(TagParser, TestIsNotClosingTagIfThereIsSlashInAttributes)
{
    const std::string TAG = "<script type=\"text/javascript\">";

    EXPECT_FALSE(IsClosingTag(TAG));
}

TEST(TagParser, TestThrowIfTagContainsOnlyBeginAndTrailingSpaces)
{
    const std::string TAG = "< ";

    EXPECT_THROW(IsClosingTag(TAG), std::logic_error);
}