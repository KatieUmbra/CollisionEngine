CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(coll LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lm)

find_package(SDL2 REQUIRED)

set(SOURCES
    src/main.c
    src/keybindings.c
    src/engine/math.c
    src/engine/game.c
    )

add_executable(main ${SOURCES})
target_include_directories(main PUBLIC ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
