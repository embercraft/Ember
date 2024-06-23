cmake_minimum_required(VERSION 3.20)
project(EmberEngine VERSION 1.0 LANGUAGES CXX C)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set C Standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Print the C++ and C standard versions
message(STATUS "Using C++ standard version ${CMAKE_CXX_STANDARD}")
message(STATUS "Using C standard version ${CMAKE_C_STANDARD}")

# Set the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
    set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "" FORCE)
endif()

# Check X11 or Wayland and set the appropriate GLFW backend flag
set(GLFW_BACKEND_X11 0)
set(GLFW_BACKEND_WAYLAND 0)

if(UNIX AND NOT APPLE)
    find_package(X11)
    if(X11_FOUND)
        set(GLFW_BACKEND_X11 1)
        message(STATUS "Using X11 backend")
    else()
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(WAYLAND REQUIRED wayland-client wayland-cursor)

        if(WAYLAND_FOUND)
            set(GLFW_BACKEND_WAYLAND 1)
            message(STATUS "Using Wayland backend")
        else()
            message(FATAL_ERROR "Neither X11 nor Wayland found")
        endif()
    endif()
endif()

# Set the output directories
if(BUILD_SHARED_LIBS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-SHARED/)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-SHARED/)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-SHARED/)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-STATIC/)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-STATIC/)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}-STATIC/)
endif()

# Include subdirectories
add_subdirectory(Ember)
add_subdirectory(Sandbox)

# Set common compile options
function(set_common_compile_options target)
    target_compile_options(${target} PRIVATE
        $<$<CONFIG:DEBUG>:
            -O0
            -g
            -Wall
            -Wextra
            -pedantic
            -Wshadow
            -Wconversion
            -Wsign-conversion
            -Wunreachable-code
        >
        $<$<CONFIG:RELEASE>:
            -O3
            -Wall
            -Wextra
            -pedantic
        >
    )
endfunction()

set_common_compile_options(Sandbox)
set_common_compile_options(Ember)
