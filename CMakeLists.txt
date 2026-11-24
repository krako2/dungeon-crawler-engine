cmake_minimum_required(VERSION 3.25.1...4.0)
project(dungeon-crawler
    VERSION 1.0
    DESCRIPTION "A simple dungeon crawler game designed for the terminal"
    LANGUAGES C
)

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    if(MSVC)
        add_compile_options(/Zi)
    else()
        add_compile_options(-g)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        add_compile_options(/Ox)
    else()
        add_compile_options(-O3)
    endif()
endif()

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)

add_executable(${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    include
)

add_subdirectory(src)
