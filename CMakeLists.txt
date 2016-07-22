cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

option(GEC_BUILD_EXAMPLES "Build Examples" ON)

#set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
#set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

#if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
#    message(SEND_ERROR "In-source builds are not allowed.")
#endif ()

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

set(MACOSX_RPATH "")

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(sources/ext/glfw)

# Bullet Physics
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(sources/ext/bullet3)
include(sources/ext/bullet3/UseBullet.cmake)

# Assimp
add_subdirectory(sources/ext/assimp)

# Python
ExternalProject_Add(
        python3
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources/ext/cpython
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/source/ext/cpython/configure --prefix=<INSTALL_DIR> --enable-sharedb --with-pymalloc
        BUILD_COMMAND ${MAKE}
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
        BUILD_IN_SOURCE 1
        BUILD_DIR ${PROJECT_BINARY_DIR}/cpython
)
include_directories(sources/ext/cpython/Include)
link_directories(${PROJECT_BINARY_DIR}/cpython)

## BUILD

add_subdirectory(sources/GameEngineC)

if(GEC_BUILD_EXAMPLES)
    if(GEC_BUILD_EXAMPLES STREQUAL "ON")
        add_subdirectory(sources/examples)
    endif()
endif()