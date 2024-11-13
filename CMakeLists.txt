cmake_minimum_required(VERSION 3.15)

project(toco)

add_executable(toco src/main.cpp)

install(TARGETS toco DESTINATION bin)