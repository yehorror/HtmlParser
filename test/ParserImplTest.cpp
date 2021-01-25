#include <gtest/gtest.h>

#include "../HtmlParser/ParserImpl.hpp"

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

TEST(ParserImlTest, TestThrowIfEndTagIsNotEqualsBeginTag)
{
    const std::string HTML = "<head></body>";

    Impl::Parser parser(HTML);
    EXPECT_THROW(parser.Parse(), std::logic_error);
}
