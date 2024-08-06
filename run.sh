#!/bin/bash

# Setting up trap to handle exit status
trap 'EXIT_STATUS=$?; if [ $EXIT_STATUS -eq 0 ]; then echo -e "\033[32mProgram exited successfully.\033[0m"; else echo -e "\033[31mProgram exited with status $EXIT_STATUS.\033[0m"; fi' EXIT

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the project directory
cd "$SCRIPT_DIR" || { echo -e "\033[31mFailed to navigate to the script directory.\033[0m"; exit 1; }

# Function to create and set up the Python virtual environment
setup_python_env() {
    local venv_dir="$SCRIPT_DIR/.venv"

    # Check if the virtual environment already exists
    if [ ! -d "$venv_dir" ]; then
        echo "Creating virtual environment in $venv_dir"
        python3 -m venv "$venv_dir" || { echo -e "\033[31mFailed to create virtual environment.\033[0m"; exit 1; }
    else
        echo "Virtual environment already exists in $venv_dir"
    fi

    # Activate the virtual environment
    source "$venv_dir/bin/activate"

    # Check if necessary Python packages are already installed
    if ! python -c "import requests" &> /dev/null; then
        echo "Installing requests package"
        pip install requests || { echo -e "\033[31mFailed to install requests package.\033[0m"; exit 1; }
    else
        echo "requests package is already installed"
    fi

    if ! python -c "import fake_useragent" &> /dev/null; then
        echo "Installing fake-useragent package"
        pip install fake-useragent || { echo -e "\033[31mFailed to install fake-useragent package.\033[0m"; exit 1; }
    else
        echo "fake-useragent package is already installed"
    fi
}

setup_python_env

./Scripts/Vulkan.py

# Initialize variables
NINJA=true
BUILD_TYPE="Debug"
GPU=false
CLEAN=false
LIB_TYPE="Static"
VERBOSE=false
PARALLEL=true
FOUNDRY=true

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
        ("p")
            PARALLEL=false
            ;;
        ("v")
            VERBOSE=true
            ;;
        ("c")
            CLEAN=true
            ;;
        ("s")
            LIB_TYPE="Shared"
            ;;
        ("g")
            GPU=true
            ;;
        ("f")
            FOUNDRY=false
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
echo -e "\033[34mRunning with the following properties:\033[0m"

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
echo -e "\033[34mParallel Build: $PARALLEL\033[0m"
echo -e "\033[34mVerbose: $VERBOSE\033[0m"
echo -e "\033[34mClean Build: $CLEAN\033[0m"
echo -e "\033[34mLibrary Type (Shared/Static): $LIB_TYPE\033[0m"

# Set GPU support environment variables if necessary
if [ "$GPU" = true ]; then
    if ! nvidia-smi &> /dev/null; then
        if ! rocm-smi &> /dev/null; then
            echo -e "\033[31mNo NVIDIA or AMD GPU found.\033[0m"
            echo -e "\033[31mRunning without GPU support.\033[0m"
            GPU=false
        else
            export HSA_ENABLE_SDMA=0
            export HSA_ENABLE_SDMA=1
            echo -e "\033[34mGPU: AMD\033[0m"
        fi
    else
        export __NV_PRIME_RENDER_OFFLOAD=1
        export __GLX_VENDOR_LIBRARY_NAME=nvidia
        echo -e "\033[34mGPU: NVIDIA\033[0m"
    fi
fi

# Set the executable path
if [ "$FOUNDRY" = true ]; then
    echo -e "\033[34mStartup Project: Foundry\033[0m"
    EXECUTABLE="./Foundry"
else
    echo -e "\033[34mStartup Project: Sandbox\033[0m"
    EXECUTABLE="./Sandbox"
fi

echo -e "\033[34m#############################################\033[0m"
echo " "

# Remove existing build directory if it exists and the clean flag is set
if [ "$CLEAN" = true ]; then
    if [ -d "build" ]; then
        rm -rf build || { echo -e "\033[31mFailed to remove build directory.\033[0m"; exit 1; }
    fi
fi

# Create build directory and configure project
if [ "$LIB_TYPE" = "Shared" ]; then
    if [ "$NINJA" = true ]; then
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="ON" -G Ninja || exit $?
    else
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="ON" || exit $?
    fi
else
    if [ "$NINJA" = true ]; then
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="OFF" -G Ninja || exit $?
    else
        cmake -S . -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="OFF" || exit $?
    fi
fi

# Build the project
BUILD_FLAGS=""
if [ "$VERBOSE" = true ]; then
    if [ "$NINJA" = true ]; then
        BUILD_FLAGS="-v"
    else
        BUILD_FLAGS="-- VERBOSE=1"
    fi
fi

if [ "$PARALLEL" = true ]; then
    cmake --build build/ --config "$BUILD_TYPE" --parallel $BUILD_FLAGS || exit $?
else
    cmake --build build/ --config "$BUILD_TYPE" $BUILD_FLAGS || exit $?
fi

# Change to the appropriate directory and run the executable
if [ "$FOUNDRY" = true ]; then
    cd Foundry/ || { echo -e "\033[31mFailed to navigate to the Foundry directory.\033[0m"; exit 1; }
    echo -e "\033[34mRunning Foundry.\033[0m"
    "../build/$BUILD_TYPE-$LIB_TYPE/Foundry/Foundry" || { echo -e "\033[31mFailed to run the executable.\033[0m"; exit 1; }
else
    cd Sandbox/ || { echo -e "\033[31mFailed to navigate to the Sandbox directory.\033[0m"; exit 1; }
    echo -e "\033[34mRunning Sandbox.\033[0m"
    "../build/$BUILD_TYPE-$LIB_TYPE/Sandbox/Sandbox" || { echo -e "\033[31mFailed to run the executable.\033[0m"; exit 1; }
fi
