#include <gtest/gtest.h>

#include "../HtmlParser/Parser.hpp"

using namespace HtmlParser;

TEST(ParseTest, TestThrowOnEmptyInput)
{
    const std::string EMPTY_STRING = "";
    EXPECT_THROW(Parse(EMPTY_STRING), std::logic_error);
}
