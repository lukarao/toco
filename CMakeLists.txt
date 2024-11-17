cmake_minimum_required(VERSION 3.15)

project(toco)

set(SOURCES
    src/builder.cpp
    src/lexer.cpp
    src/main.cpp
    src/parser.cpp
)

add_executable(toco ${SOURCES})

install(TARGETS toco DESTINATION bin)