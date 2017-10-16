cmake_minimum_required(VERSION 3.7)
project(lex)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lex.h)
add_executable(lex ${SOURCE_FILES})