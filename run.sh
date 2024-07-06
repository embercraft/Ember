#!/bin/bash

# Setting up trap to handle exit status
trap 'EXIT_STATUS=$?; if [ $EXIT_STATUS -eq 0 ]; then echo -e "\033[32mProgram exited successfully.\033[0m"; else echo -e "\033[31mProgram exited with status $EXIT_STATUS.\033[0m"; fi' EXIT

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the script directory
cd "$SCRIPT_DIR" || { echo -e "\033[31mFailed to navigate to the script directory.\033[0m"; exit 1; }

# Initialize variables
BUILD_TYPE="Debug"
GPU=false
CLEAN=false
LIB_TYPE="Static"
ASSERTS="ON"

# Parse arguments
for arg in "$@"; do
    case "${arg,,}" in
        ("r")
            BUILD_TYPE="Release"
            ;;
        ("g")
            GPU=true
            ;;
        ("c")
            CLEAN=true
            ;;
        ("s")
            LIB_TYPE="Shared"
            ;;
        ("a")
            ASSERTS="OFF"
            ;;
    esac
done

# Print properties
echo " "
echo -e "\033[34m#############################################\033[0m"
echo -e "\033[34mRunning with the following properties:\033[0m"
echo -e "\033[34mBuild Type: $BUILD_TYPE\033[0m"
echo -e "\033[34mClean Build: $CLEAN\033[0m"
echo -e "\033[34mLibrary Type (Shared/Static): $LIB_TYPE\033[0m"
echo -e "\033[34mGPU Support: $GPU\033[0m"
echo -e "\033[34m#############################################\033[0m"
echo " "

# Set the executable path based on the build type
EXECUTABLE="./Sandbox"

# Remove existing build directory if it exists and the clean flag is set
if [ "$CLEAN" = true ]; then
    if [ -d "build" ]; then
        rm -rf build || { echo -e "\033[31mFailed to remove build directory.\033[0m"; exit 1; }
    fi
fi

# Create build directory
if [ "$LIB_TYPE" = "Shared" ]; then
    cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="ON" -DEMBER_ENABLE_ASSERTS="$ASSERTS" || exit $?
else
    cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="OFF" -DEMBER_ENABLE_ASSERTS="$ASSERTS" || exit $?
fi

# Build the project
cmake --build build/ || exit $?

# Set GPU support environment variables if necessary
if [ "$GPU" = true ]; then
    if ! nvidia-smi &> /dev/null; then
        echo -e "\033[31mNVIDIA GPU not found.\033[0m"
        echo -e "\033[31mRunning without GPU support.\033[0m"
    else
        export __NV_PRIME_RENDER_OFFLOAD=1
        export __GLX_VENDOR_LIBRARY_NAME=nvidia
    fi
fi

# Copy assets to the build directory
echo -e "\033[34mCopying assets to the build directory.\033[0m"
rm -rf "build/$BUILD_TYPE-$LIB_TYPE/Sandbox/assets" || { echo -e "\033[31mFailed to remove assets directory.\033[0m"; exit 1; }
cp -r Sandbox/assets build/$BUILD_TYPE-$LIB_TYPE/Sandbox/ || { echo -e "\033[31mFailed to copy assets to the build directory.\033[0m"; exit 1; }

# Change to the build directory
cd build/$BUILD_TYPE-$LIB_TYPE/Sandbox/ || { echo -e "\033[31mFailed to navigate to the build directory.\033[0m"; exit 1; }

# Run the executable 
"$EXECUTABLE"
