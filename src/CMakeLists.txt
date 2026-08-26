target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    main.c
    game.c
    file.c
    util.c
    debug.c
    challenge.c
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
