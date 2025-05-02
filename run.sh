# #!/bin/bash

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
}

setup_python_env

./Scripts/Setup.py

./Scripts/Vulkan.py

# Initialize default values
NINJA=true
BUILD_TYPE="Debug"
GPU=false
CLEAN=false
LIB_TYPE="Static"
VERBOSE=false
PARALLEL=true
FOUNDRY=true
COMPILE_ENGINE=true
COMPILE_FOUNDRY=true

# Parse arguments
for arg in "$@"; do
    case "${arg,,}" in
        ("n")  NINJA=false ;;
        ("r")  BUILD_TYPE="Release" ;;
        ("mr") BUILD_TYPE="MinSizeRel" ;;
        ("rd") BUILD_TYPE="RelWithDebInfo" ;;
        ("p")  PARALLEL=false ;;
        ("v")  VERBOSE=true ;;
        ("c")  CLEAN=true ;;
        ("s")  LIB_TYPE="Shared" ;;
        ("g")  GPU=true ;;
        ("f")  FOUNDRY=false ;;
        ("ce") COMPILE_ENGINE=false ;;
        ("cf") COMPILE_FOUNDRY=false ;;
        (*) echo -e "\033[31mInvalid argument: $arg\033[0m" ;;
    esac
done

# Initialize args1 and args2
args1=""
args2=""

if [ "$COMPILE_ENGINE" = true ]; then
	args1+=" -DCOMPILE_ENGINE=ON"
else
	args1+=" -DCOMPILE_ENGINE=OFF"
fi
if [ "$COMPILE_FOUNDRY" = true ]; then
	args1+=" -DCOMPILE_FOUNDARY=ON"
else
	args1+=" -DCOMPILE_FOUNDARY=OFF"
fi

# Print config summary
echo " "
echo -e "\033[34m#############################################\033[0m"
echo -e "\033[34mRunning with the following properties:\033[0m"

# Check for ninja
if $NINJA && ninja --version &> /dev/null; then
    echo -e "\033[34mBuild System: Ninja\033[0m"
    args1+=" -G Ninja"
else
    NINJA=false
    echo -e "\033[34mBuild System: Make (default)\033[0m"
fi

echo -e "\033[34mBuild Type: $BUILD_TYPE\033[0m"
echo -e "\033[34mParallel Build: $PARALLEL\033[0m"
echo -e "\033[34mVerbose: $VERBOSE\033[0m"
echo -e "\033[34mClean Build: $CLEAN\033[0m"
echo -e "\033[34mLibrary Type (Shared/Static): $LIB_TYPE\033[0m"

# Handle GPU detection
if $GPU; then
    if nvidia-smi &> /dev/null; then
        export __NV_PRIME_RENDER_OFFLOAD=1
        export __GLX_VENDOR_LIBRARY_NAME=nvidia
        echo -e "\033[34mGPU: NVIDIA\033[0m"
    elif rocm-smi &> /dev/null; then
        export HSA_ENABLE_SDMA=0
        export HSA_ENABLE_SDMA=1
        echo -e "\033[34mGPU: AMD\033[0m"
    else
        echo -e "\033[31mNo GPU found. Disabling GPU support.\033[0m"
        GPU=false
    fi
fi

# Determine startup project
EXECUTABLE=""
if $FOUNDRY; then
    EXECUTABLE="./Foundry"
    echo -e "\033[34mStartup Project: Foundry\033[0m"
else
    EXECUTABLE="./Sandbox"
    echo -e "\033[34mStartup Project: Sandbox\033[0m"
fi

echo -e "\033[34m#############################################\033[0m"
echo " "

# Clean build
if $CLEAN && [ -d "build" ]; then
    rm -rf build || { echo -e "\033[31mFailed to remove build directory.\033[0m"; exit 1; }
fi

# Compose args1 for configuration
args1+=" -DCMAKE_BUILD_TYPE=$BUILD_TYPE"
if [ "$LIB_TYPE" = "Shared" ]; then
    args1+=" -DBUILD_SHARED_LIBS=ON"
else
    args1+=" -DBUILD_SHARED_LIBS=OFF"
fi

# Compose args2 for build
if $VERBOSE; then
    if $NINJA; then
        args2+=" -v"
    else
        args2+=" -- VERBOSE=1"
    fi
fi

if $PARALLEL; then
    CORES=$(nproc)
    args2+=" --parallel $CORES"
fi

# Run configuration
cmake -S . -B build/ $args1 || exit $?

# Build
cmake --build build/ $args2 || exit $?

# Run the executable
if $FOUNDRY; then
    cd Foundry/ || { echo -e "\033[31mFailed to navigate to Foundry.\033[0m"; exit 1; }
    echo -e "\033[34mRunning Foundry.\033[0m"
    "../build/$BUILD_TYPE-$LIB_TYPE/Foundry/Foundry" || exit 1
else
    cd Sandbox/ || { echo -e "\033[31mFailed to navigate to Sandbox.\033[0m"; exit 1; }
    echo -e "\033[34mRunning Sandbox.\033[0m"
    "../build/$BUILD_TYPE-$LIB_TYPE/Sandbox/Sandbox" || exit 1
fi
