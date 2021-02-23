#include <gtest/gtest.h>
#include "Impl/HtmlStream/HtmlStream.hpp"

using namespace HtmlParser::Impl;

TEST(HtmlStreamTest, TestReadingOfATagFromStream)
{
    const std::string HTML = "<body> whatever content that won't be parsed </body>";

    HtmlStream stream(HTML);
    const std::string parsedTag = stream.ReadTag();

    EXPECT_EQ(parsedTag, "<body>");
}