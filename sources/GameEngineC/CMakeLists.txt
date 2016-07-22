cmake_minimum_required(VERSION 3.5)

project(GameEngineC C CXX)

file(GLOB CPP_FILES source/*.cpp)

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})

# GLFW
target_link_libraries(${PROJECT_NAME} glfw)

# Assimp
target_link_libraries(${PROJECT_NAME} assimp)

# Bullet Physics
target_link_libraries(${PROJECT_NAME} BulletInverseDynamics)
target_link_libraries(${PROJECT_NAME} BulletSoftBody)
target_link_libraries(${PROJECT_NAME} BulletDynamics)
target_link_libraries(${PROJECT_NAME} BulletCollision)
target_link_libraries(${PROJECT_NAME} LinearMath)

# Python
target_link_libraries(${PROJECT_NAME} python)

# OpenGL
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_glu_LIBRARY})

set(${PROJECT_NAME}_DEFINITIONS
        CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
        ${GLFW_SOURCE_DIR}/include
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)