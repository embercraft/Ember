# Define minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Define project and languages
project(Ember CXX)

# Define library sources
file(GLOB_RECURSE EMBER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Ember/*.cpp")
file(GLOB_RECURSE EMBER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/Ember/*.h")

# Create library
if(BUILD_SHARED_LIBS)
    add_library(Ember SHARED ${EMBER_SOURCES} ${EMBER_HEADERS})
else()
    add_library(Ember STATIC ${EMBER_SOURCES} ${EMBER_HEADERS})
endif()

# Add subdirectory for spdlog
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog)

# Include directories
target_include_directories(Ember
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include
)

# Define preprocessor definitions
if(UNIX AND NOT APPLE)
    target_compile_definitions(Ember PRIVATE EMBER_PLATFORM_LINUX EMBER_BUILD_LIB)
elseif(WIN32)
    target_compile_definitions(Ember PRIVATE EMBER_PLATFORM_WINDOWS EMBER_BUILD_LIB)
endif()

# Link spdlog to Ember
target_link_libraries(Ember PRIVATE spdlog)

# Precompiled headers
target_precompile_headers(Ember PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Emberpch.h)

# Set C++ standard
target_compile_features(Ember PUBLIC cxx_std_17)
