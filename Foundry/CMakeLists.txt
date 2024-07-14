# Define minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Define project and languages
project(Foundry CXX)

# Define executable sources
file(GLOB_RECURSE FOUNDRY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE FOUNDRY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# Create executable
add_executable(Foundry ${FOUNDRY_SOURCES} ${FOUNDRY_HEADERS})

# Set Output directory
set_target_properties(Foundry PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Foundry/
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Foundry/
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Foundry/
)

# Link Ember and other libraries
target_link_libraries(Foundry PRIVATE EmberEngine)

# Include directories
target_include_directories(Foundry
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ember/Vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ember/Vendor
        ${CMAKE_CURRENT_SOURCE_DIR}/../Ember/src
)

# Define preprocessor definitions
if(UNIX AND NOT APPLE)
    target_compile_definitions(Foundry PRIVATE EMBER_PLATFORM_LINUX)
elseif(WIN32)
    target_compile_definitions(Foundry PRIVATE EMBER_PLATFORM_WINDOWS)
endif()

# Set C++ standard
target_compile_features(Foundry PRIVATE cxx_std_17)

add_custom_command(TARGET Foundry POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Foundry/assets
)
