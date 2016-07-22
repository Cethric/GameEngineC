cmake_minimum_required(VERSION 3.5)
project(Example C CXX)

set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source/)

file(GLOB CPP_FILES source/*.cpp)

add_definitions(${GameEngineC_DEFINITIONS})
include_directories(${GameEngineC_INCLUDE_DIRS})

link_libraries(GameEngineC)
add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} GameEngineC)
target_link_libraries(${PROJECT_NAME} assimp)