cmake_minimum_required(VERSION 3.17)

project(HtmlParserTest)

add_subdirectory(googletest)
add_subdirectory(HtmlParser)

include_directories(
    ${gtest_SOURCE_DIR}/include 
    ${gtest_SOURCE_DIR}

    ./HtmlParser
)

add_executable(HtmlParserTest
    test/NodeTest.cpp
    test/ParserTest.cpp
    test/ParserImplTest.cpp
    test/TagParserTest.cpp
    test/AttributesParserTest.cpp
)

target_link_libraries(HtmlParserTest 
    gtest 
    gtest_main 
    gmock
    HtmlParser
)