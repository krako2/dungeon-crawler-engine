target_sources(${CMAKE_PROJECT_NAME} PRIVATE main.c)

add_subdirectory(debug)
add_subdirectory(file)
add_subdirectory(game)
add_subdirectory(util)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    debug
    file
    game
    util
)