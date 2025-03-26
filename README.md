# Ember

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Platform](https://img.shields.io/badge/platform-linux-lightgrey)

![Banner](Resources/Banner.png)

Ember is a versatile game engine under active development, designed for 2D and 3D game development. It aims to provide a robust rendering pipeline, intuitive user interface, and a powerful Entity Component System (ECS). Future plans include implementing a node-based visual scripting system to enhance usability and flexibility for developers.

## Table of Contents

- [Features](#features)
- [Installation](#installation)

## Features

### Currently Available

- **Telemetry**: Provides detailed logging of function calls, durations, and call hierarchy, viewable in a web browser.
- **2D Rendering**: Utilizes an efficient OpenGL-based pipeline for 2D graphics.
- **Batch Rendering**: Enhanced rendering performance through optimized batch processing.
- **Texture Atlas**: Supports texture atlases for efficient texture management and rendering.
- **User Interface (UI)**: Intuitive interface for seamless interaction and development.
- **Entity Component System (ECS)**: Flexible system for efficient game object management.

### Coming Soon

- **Command Line Interface (CLI)**: Enables real-time engine control and command execution directly from the terminal.
- **3D Rendering**: Expanding capabilities to include advanced 3D rendering features.
- **Node-Based Visual Scripting**: Introducing a visual scripting system for intuitive game logic creation.
- **Tiling**: Enhancing the renderer with efficient tile-based rendering techniques for improved performance.
- **Sound System**: Implementing audio capabilities for immersive game experiences.
- **Hardware Profiling**: Integrating tools for monitoring and optimizing hardware performance.
- **API**: Vulkan support is planned for upcoming updates.


### Installation

To get started with Ember Engine, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone --recursive https://github.com/embercraft/Ember.git
    cd Ember
    ```

2. **Build and Run**:
    ```bash
    chmod +x run.sh
    ./run.sh
    ```

   **Arguments for `run.sh`**:

   The `run.sh` script supports several single-letter arguments to customize the build process:

   - **`n`**: Disable Ninja build system (default is true).
   - **`r`**: Set build type to Release (default is Debug).
   - **`mr`**: Set build type to MinSizeRel.
   - **`rd`**: Set build type to RelWithDebInfo.
   - **`p`**: Disable parallel build option.
   - **`v`**: Enable verbose output.
   - **`c`**: Clean build by removing existing build directory before compiling.
   - **`s`**: Build shared libraries (default is static).
	- **`g`**: Launch with dedicated GPU if available (NVIDIA & AMD GPUs over integrated ones)
   - **`f`**: Set Sandbox as Startup Project (Default is Foundry)

   Example usage:
   
   ```bash
   ./run.sh r g		# Build in Release mode & launch with dedicated GPU
   ```

   For a detailed explanation of each argument and its effect on the build process, refer to the comments in `run.sh`.
