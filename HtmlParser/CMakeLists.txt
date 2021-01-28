cmake_minimum_required(VERSION 3.5)

project(HtmlParser)

add_library(HtmlParser
    Node.cpp
    Parser.cpp
    ParserImpl.cpp
    ParserConstants.cpp
    TagParser.cpp
)
