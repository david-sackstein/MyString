cmake_minimum_required(VERSION 3.8)
project(MyString)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES MyString.h MyString.c)
add_executable(MyString ${SOURCE_FILES})