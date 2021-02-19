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

TEST(ParserImplTest, TestThrowIfOpenTagHasNoEnd)
{
    const std::string HTML = "<title";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}

TEST(ParserImplTest, TestThrowIfClosingTagHasNoEnd)
{
    const std::string HTML = "<title></title";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}

TEST(ParserImplTest, TestParsingOfInnerTags)
{
    const std::string HTML = "<head><title>Hello</title></head>";

    Impl::Parser parser(HTML);
    Node headNode = parser.Parse();
    EXPECT_EQ(headNode.GetTagName(), "head");

    Node title = headNode.GetChildNode(0);
    EXPECT_EQ(title.GetTagName(), "title");
    EXPECT_EQ(title.GetValue(), "Hello");
}

TEST(ParserImplTest, TestParsingOfMultipleInnerTags)
{    
    const std::string HTML = 
        "<head>"
            "<title>Hello</title>"
            "<script>alert('Hello');</script>"
        "</head>";

    Impl::Parser parser(HTML);
    Node headNode = parser.Parse();
    EXPECT_EQ(headNode.GetTagName(), "head");

    Node title = headNode.GetChildNode(0);
    EXPECT_EQ(title.GetTagName(), "title");
    EXPECT_EQ(title.GetValue(), "Hello");

    Node script = headNode.GetChildNode(1);
    EXPECT_EQ(script.GetTagName(), "script");
    EXPECT_EQ(script.GetValue(), "alert('Hello');");
}

TEST(ParserImplTest, TetsThrowOnCorruptedTagsInput)
{    
    const std::string HTML = 
        "<head>"
            "<title>Hello</title>"
            "<scriptalert('Hello');</script>"
        "</head>";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}