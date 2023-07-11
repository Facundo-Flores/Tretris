cmake_minimum_required(VERSION 3.25)
project(ClassyClash)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 3.0 QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)
    FETCHCONTENT_DECLARE(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif ()

add_executable(Tretris main.cpp Tretris.cpp Tretris.h Pieces.h Piece.cpp Piece.h Grid.cpp Grid.h Images.cpp Images.h)

target_link_libraries(Tretris PRIVATE raylib)