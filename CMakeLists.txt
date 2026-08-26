cmake_minimum_required(VERSION 3.25.1...4.0)
project(dungeon-crawler
    VERSION 1.0
    DESCRIPTION "A simple dungeon crawler game designed for the terminal"
    LANGUAGES C
)

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -ansi
        -Weverything
        -Werror
        -Wno-unsafe-buffer-usage
        -Wno-covered-switch-default
        -Wno-missing-noreturn
    )
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Please use Clang to compile this program.")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g)
    add_compile_definitions(DEBUG)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)
