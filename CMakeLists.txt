cmake_minimum_required(VERSION 3.5)

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
)

target_link_libraries(HtmlParserTest 
    gtest 
    gtest_main 
    gmock
    HtmlParser
)
