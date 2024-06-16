#!/bin/bash

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the script directory
cd "$SCRIPT_DIR" || ( echo -e "\033[31mFailed to navigate to the script directory.\033[0m" && exit 1 )

# Initialize variables
BUILD_TYPE="Debug"
TIMED_RUN=false
DELETE_BUILD=false
GPU=false
CLEAN=false
SHARED=false

# Parse arguments
for arg in "$@"; do
    case "${arg,,}" in
        ("r")
            BUILD_TYPE="Release"
            ;;
        ("d")
            BUILD_TYPE="Debug"
            ;;
        ("t")
            TIMED_RUN=true
            ;;
        ("b")
            DELETE_BUILD=true
            ;;
        ("g")
            GPU=true
            ;;
        ("c")
            CLEAN=true
            ;;
        ("s")
            SHARED=true
            ;;
    esac
done

echo -e "\033[34mBuilding in $BUILD_TYPE mode...\033[0m"

# Remove existing build directory if it exists and the clean flag is set
if [ "$CLEAN" = true ]; then
    echo -e "\033[34mDoing a Clean Build.\033[0m"
    if [ -d "build" ]; then
        rm -rf build
    fi
fi

# Generate Makefiles and build the project with the specified build type
if [ "$SHARED" = true ]; then
    echo -e "\033[34mBuilding shared libraries...\033[0m"
    cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS=ON
else
    cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
fi

# Build the project
cmake --build build/

# Determine the executable path
if [ "$GPU" = true ]; then
    if ! nvidia-smi &> /dev/null; then
        echo -e "\033[31mNVIDIA GPU not found.\033[0m"
    else
        echo -e "\033[34mRunning with GPU support...\033[0m"
        export __NV_PRIME_RENDER_OFFLOAD=1
        export __GLX_VENDOR_LIBRARY_NAME=nvidia
    fi
fi
EXECUTABLE="./build/Sandbox/Sandbox"

# Run the executable with the remaining arguments
if [ "$TIMED_RUN" = true ]; then
    eval "time $EXECUTABLE"
else
    eval "$EXECUTABLE"
fi

# Get the exit status of the program
EXIT_STATUS=$?
if [ $EXIT_STATUS -eq 0 ]; then
    echo -e "\033[32mProgram exited successfully.\033[0m"
else
    echo -e "\033[31mProgram exited with status $EXIT_STATUS.\033[0m"
fi

# Check if the build directory should be deleted
if [ "$DELETE_BUILD" = true ]; then
    rm -rf build
    echo -e "\033[34mBuild directory deleted.\033[0m"
fi