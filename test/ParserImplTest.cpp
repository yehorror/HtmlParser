#include <gtest/gtest.h>

#include "Impl/ParserImpl.hpp"

using namespace HtmlParser;

TEST(ParserImplTest, TestParsingOfATag)
{
    const std::string HTML = "<head></head>";

    Impl::Parser parser(HTML);
    Node parsedNode = parser.Parse();

    EXPECT_EQ("head", parsedNode.GetTagName());
}

TEST(ParserImplTest, TestThrowIfContentDoesntBeginWithATag)
{
    const std::string HTML = "whatever content";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}

TEST(ParserImplTest, TestParsingOfTextBetweenTags)
{
    const std::string HTML = "<title>Hello</title>";

    Impl::Parser parser(HTML);
    Node titleNode = parser.Parse();
    EXPECT_EQ(titleNode.GetTagName(), "title");
    EXPECT_EQ(titleNode.GetValue(), "Hello");
}

TEST(ParserImplTest, TestThrowIfHTMLHaveNoClosingTag)
{
    const std::string HTML = "<title>Hello";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}

TEST(ParserImplTest, TestThrowIfClosingTagDoesntEqualsOpenTag)
{
    const std::string HTML = "<title></body>";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}