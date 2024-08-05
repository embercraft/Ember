# Define minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Define project and languages
project(EmberEngine CXX)

# Set Options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Enable testing" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Enable parse tools" FORCE)

# Define library sources
file(GLOB_RECURSE EMBERENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE EMBERENGINE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# Create library
if(BUILD_SHARED_LIBS)
    add_library(EmberEngine SHARED ${EMBERENGINE_SOURCES} ${EMBERENGINE_HEADERS})
else()
    add_library(EmberEngine STATIC ${EMBERENGINE_SOURCES} ${EMBERENGINE_HEADERS})
endif()

# Add subdirectory for dependencies
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GLFW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/Glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/EnTT)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/yaml-cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo)

# Define stb_image target
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb_image)
target_sources(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb_image/stb_image.cpp)

# Include directories
target_include_directories(EmberEngine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor    
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GLFW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/Glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGui
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/EnTT/single_include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/yaml-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/VulkanSDK/1.3.283.0/x86_64/include
)

# Set output directories
set_target_properties(EmberEngine 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/EmberEngine/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/EmberEngine/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EmberEngine/
)

set_target_properties(spdlog 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/spdlog/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/spdlog/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/spdlog/
)

set_target_properties(glfw 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/GLFW/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/GLFW/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GLFW/
)

set_target_properties(Glad
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Glad/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Glad/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Glad/
)

set_target_properties(ImGui 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/ImGui/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ImGui/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImGui/
)

set_target_properties(glm 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/glm/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/glm/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glm/
)

set_target_properties(yaml-cpp 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/yaml-cpp/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/yaml-cpp/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/yaml-cpp/
)

set_target_properties(ImGuizmo 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/ImGuizmo/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ImGuizmo/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImGuizmo/
)

# Find Packages
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

# Set VulkanSDK lib path
set(VULKAN_SDK_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/VulkanSDK/1.3.283.0/x86_64/lib)

# Define preprocessor definitions
target_compile_definitions(EmberEngine PRIVATE GLFW_INCLUDE_NONE)

if(UNIX AND NOT APPLE)
    target_compile_definitions(EmberEngine PRIVATE EMBER_PLATFORM_LINUX)
elseif(WIN32)
    target_compile_definitions(EmberEngine PRIVATE EMBER_PLATFORM_WINDOWS)
endif()

# Link libraries
target_link_libraries(EmberEngine
    PUBLIC
        spdlog
        glfw
        Glad
        ImGui
        glm
        stb_image
        EnTT
        yaml-cpp
        ImGuizmo
        ${CMAKE_DL_LIBS}
        Threads::Threads
        OpenGL::GL
        ${VULKAN_SDK_LIB_PATH}/libvulkan.so
        ${VULKAN_SDK_LIB_PATH}/libshaderc_combined.a
        ${VULKAN_SDK_LIB_PATH}/libSPIRV-Tools.a
        ${VULKAN_SDK_LIB_PATH}/libspirv-cross-core.a
        ${VULKAN_SDK_LIB_PATH}/libspirv-cross-glsl.a
)

# Precompiled headers
target_precompile_headers(EmberEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Emberpch.h)

# Exclude specific files from using precompiled headers (PCH)
target_sources(ImGuizmo PRIVATE
    # ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/GraphEditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/ImCurveEdit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/ImGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/ImSequencer.cpp
)

set_source_files_properties(
    # ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/GraphEditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/ImCurveEdit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/ImGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/ImGuizmo/ImSequencer.cpp
    PROPERTIES
    COMPILE_FLAGS "-fno-implicit-templates"
)
