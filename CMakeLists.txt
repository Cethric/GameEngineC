cmake_minimum_required(VERSION 3.4)
include(ExternalProject)

cmake_policy(VERSION 3.5)
set(CMAKE_MACOSX_RPATH 1)
#cmake_policy(SET CMP0042 NEW)

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

if (APPLE)
    message("Generating files for Apple OSX")
endif ()

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(sources/ext/glfw)

# Bullet Physics
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)

add_subdirectory(sources/ext/bullet3)
include(sources/ext/bullet3/UseBullet.cmake)

# Assimp
add_subdirectory(sources/ext/assimp)

# Python
set(PYTHON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources/ext/cpython/install_debug")
set(PYTHON_INCLUDE_DIR "${PYTHON_DIR}/include/python3.6dm")
include_directories(${PYTHON_INCLUDE_DIR})
if (APPLE)
    find_library(
            libpython3.6dm.dylib
            PATHS ${PYTHON_DIR}
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
    )
elseif (UNIX)
#    message(FATAL_ERROR "Cannot build for a unix environment other than OSX")
    find_library(
            libpython3.6dm.so
            PATHS ${PYTHON_DIR}
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
    )
elseif (WINDOWS)
    message(FATAL_ERROR "Cannot build for a windows environment")
endif ()

# Ant Tweak Bar
set(ANTTWEAKBAR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources/ext/anttweakbar")
set(ANTTWEAKBAR_INCLUDE_DIR "${ANTTWEAKBAR_DIR}/include")
include_directories(${ANTTWEAKBAR_INCLUDE_DIR})
if (APPLE)
    #    execute_process(
    #            COMMAND cd ${ANTTWEAKBAR_DIR}/src
    #            COMMAND make -f Makefile.osx
    #    )
    find_library(
            libAntTweakBar.dylib
            PATHS ${ANTTWEAKBAR_DIR}/lib/
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
    )
elseif (UNIX)
    find_library(
            libAntTweakBar.so
            PATHS ${ANTTWEAKBAR_DIR}/lib/
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
    )
#    message(FATAL_ERROR "Cannot build for a unix environment other than OSX")
elseif (WINDOWS)
    message(FATAL_ERROR "Cannot build for a windows environment")
endif ()

# GLM
set(GLM_DYNAMIC_LIBRARY_ENABLE ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "" FORCE)
add_subdirectory(sources/ext/glm)

# OpenEXR (Optional for DevIL)
option(GEC_BUILD_OPENEXR "Build OpenEXR library for use with DevIL." OFF)
if (GEC_BUILD_OPENEXR)
    if (GEC_BUILD_EXAMPLES STREQUAL "ON")
        add_subdirectory(sources/ext/openexr/OpenEXR)
    endif (GEC_BUILD_EXAMPLES STREQUAL "ON")
endif (GEC_BUILD_OPENEXR)

# DevIL
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
if (GEC_BUILD_OPENEXR)
    if (GEC_BUILD_EXAMPLES STREQUAL "ON")
        set(IL_NO_EXR 0 CACHE INT "" FORCE)
    else (GEC_BUILD_EXAMPLES STREQUAL "ON")
        set(IL_NO_EXR 1 CACHE INT "" FORCE)
    endif (GEC_BUILD_EXAMPLES STREQUAL "ON")
endif (GEC_BUILD_OPENEXR)
add_subdirectory(sources/ext/devil/DevIL)


## BUILD
add_subdirectory(sources/GameEngineC)

if(GEC_BUILD_EXAMPLES)
    if(GEC_BUILD_EXAMPLES STREQUAL "ON")
        add_subdirectory(sources/examples)
    endif()
endif()