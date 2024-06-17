# Define minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Define project and languages
project(Glad C)

# Build as a shared/static library depending on the BUILD_SHARED_LIBS flag
add_library(Glad
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
)

# Define include directories
target_include_directories(Glad
    PUBLIC
        include
)
