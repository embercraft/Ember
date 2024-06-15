# Define minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Define project and languages
project(Ember CXX)

# Define library sources
file(GLOB_RECURSE EMBER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Ember/*.cpp")
file(GLOB_RECURSE EMBER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/Ember/*.h")

# Create library
add_library(Ember STATIC ${EMBER_SOURCES} ${EMBER_HEADERS})

# Add subdirectory for spdlog
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog)

# Include directories
target_include_directories(Ember
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include
)

# Define preprocessor definitions
target_compile_definitions(Ember PRIVATE EMBER_PLATFORM_LINUX EMBER_BUILD_SHARED)

# Link spdlog to Ember
target_link_libraries(Ember PRIVATE spdlog)

# Set C++ standard
target_compile_features(Ember PUBLIC cxx_std_17)
