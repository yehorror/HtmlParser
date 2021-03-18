cmake_minimum_required(VERSION 3.5)

project(HtmlParser)


add_library(HtmlParser
    Node.cpp
    Node.hpp
    
    Tag.cpp 
    Tag.hpp

    Parser.cpp
    Parser.hpp

    Impl/Utils.cpp
    Impl/Utils.hpp

    Impl/ParserImpl.cpp
    Impl/ParserImpl.hpp

    Impl/ParserConstants.cpp
    Impl/ParserConstants.hpp

    Impl/TagParsing/TagParser.cpp
    Impl/TagParsing/TagParser.hpp

    Impl/TagParsing/AttributesParser.cpp
    Impl/TagParsing/AttributesParser.hpp

    Impl/HtmlStream/HtmlStream.cpp
    Impl/HtmlStream/HtmlStream.hpp

    Impl/ParsingStrategies/AbstractParsingStrategy.hpp

    Impl/ParsingStrategies/DefaultParsingStrategy.cpp
    Impl/ParsingStrategies/DefaultParsingStrategy.hpp
)

target_include_directories(HtmlParser PRIVATE ./ ./Impl ./Impl/TagParsing)