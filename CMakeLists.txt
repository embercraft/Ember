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
