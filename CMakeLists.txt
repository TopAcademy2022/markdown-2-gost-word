cmake_minimum_required(VERSION 3.21)
project(markdown-2-gost-word LANGUAGES CXX)

if(NOT MSVC)
    message(FATAL_ERROR "This project requires MSVC (C++/CLI + CppUnitTestFramework).")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(markdown-2-gost-word)
add_subdirectory(tests/markdown-2-gost-word.Tests)