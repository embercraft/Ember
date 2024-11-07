#!/bin/bash

# Setting up trap to handle exit status
trap 'EXIT_STATUS=$?; if [ $EXIT_STATUS -eq 0 ]; then echo -e "\033[32mProgram exited successfully.\033[0m"; else echo -e "\033[31mProgram exited with status $EXIT_STATUS.\033[0m"; fi' EXIT

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the project directory
cd "$SCRIPT_DIR" || { echo -e "\033[31mFailed to navigate to the script directory.\033[0m"; exit 1; }

# Initialize variables
NINJA=true
BUILD_TYPE="Debug"
LIB_TYPE="Static"

# Parse arguments
for arg in "$@"; do
    case "${arg,,}" in
        ("n")
            NINJA=false
            ;;
        ("r")
            BUILD_TYPE="Release"
            ;;
        ("mr")
            BUILD_TYPE="MinSizeRel"
            ;;
        ("rd")
            BUILD_TYPE="RelWithDebInfo"
            ;;
        ("s")
            LIB_TYPE="Shared"
            ;;
        (*)
            echo -e "\033[31mInvalid argument: $arg\033[0m"
            # exit 1
            ;;
    esac
done

# Print properties
echo " "
echo -e "\033[34m#############################################\033[0m"
echo -e "\033[34mGenerating with the following properties:\033[0m"

# Check if Ninja is available
if [ "$NINJA" = true ]; then
    if ! ninja --version &> /dev/null; then
        echo -e "\033[31mNinja not found.\033[0m"
        echo -e "\033[31mFalling back to default build system.\033[0m"
        NINJA=false
    else
        echo -e "\033[34mBuild System: Ninja\033[0m"
    fi
fi

echo -e "\033[34mBuild Type: $BUILD_TYPE\033[0m"
echo -e "\033[34mLibrary Type (Shared/Static): $LIB_TYPE\033[0m"
echo -e "\033[34m#############################################\033[0m"
echo " "

# Create build directory and configure project
if [ "$LIB_TYPE" = "Shared" ]; then
    if [ "$NINJA" = true ]; then
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="ON" -G Ninja || exit $?
    else
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="ON" || exit $?
    fi
else
    if [ "$NINJA" = true ]; then
        cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="OFF" -G Ninja || exit $?
    else
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="OFF" || exit $?
    fi
fi
