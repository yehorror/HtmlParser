#include <gtest/gtest.h>

#include "Impl/ParserImpl.hpp"

using namespace HtmlParser;

TEST(ParserImplTest, TestParsingOfATag)
{
    const std::string HTML = "<head></head>";

    Impl::Parser parser(HTML);
    Node rootNode = parser.Parse();
    Node childNode = rootNode.GetChildNode(0);

    EXPECT_EQ("head", childNode.GetTag().GetName());
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
    Node rootNode = parser.Parse();
    Node titleNode = rootNode.GetChildNode(0);
    EXPECT_EQ(titleNode.GetTag().GetName(), "title");
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
    Node rootNode = parser.Parse();
    Node headNode = rootNode.GetChildNode(0);
    EXPECT_EQ(headNode.GetTag().GetName(), "head");

    Node title = headNode.GetChildNode(0);
    EXPECT_EQ(title.GetTag().GetName(), "title");
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
    Node rootNode = parser.Parse();
    Node headNode = rootNode.GetChildNode(0);
    EXPECT_EQ(headNode.GetTag().GetName(), "head");

    Node title = headNode.GetChildNode(0);
    EXPECT_EQ(title.GetTag().GetName(), "title");
    EXPECT_EQ(title.GetValue(), "Hello");

    Node script = headNode.GetChildNode(1);
    EXPECT_EQ(script.GetTag().GetName(), "script");
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