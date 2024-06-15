# Define minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Define project and languages
project(Sandbox CXX)

# Define executable sources
file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

# Create executable
add_executable(Sandbox ${SANDBOX_SOURCES})

# Link Ember library
target_link_libraries(Sandbox PRIVATE Ember)

# Include directories
target_include_directories(Sandbox
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Define preprocessor definitions
if(UNIX AND NOT APPLE)
    target_compile_definitions(Sandbox PRIVATE EMBER_PLATFORM_LINUX)
elseif(WIN32)
    target_compile_definitions(Sandbox PRIVATE EMBER_PLATFORM_WINDOWS)
endif()

# Set C++ standard
target_compile_features(Sandbox PRIVATE cxx_std_17)
